// Copyright Hungry Ghost


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "Components/SplineComponent.h"
#include <Input/AuraInputComponent.h>
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>

/**
 * Constructor for the AuraPlayerController class.
 * Sets the bReplicates flag to true.
 */
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

/**
 * Called when the player controller begins play.
 * Initializes the input subsystem and sets up the input mode.
 */
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && GEngine)
	{
		// ConsoleCommand(TEXT("showdebug abilitysystem"), true);
	}
	
	check(AuraContext);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

/**
 * Called to set up the input component for the player controller.
 * Binds the Move action to the Move function.
 */
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

/**
 * Called when the Move action is triggered.
 * Moves the controlled pawn based on the input values.
 * @param InputActionValue The input action value containing the move values.
 */
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// do not get confused with the following line, it is not a typo
	// the Y value is the forward value and the X value is the right value in the input mappings
	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, MoveValue.Y);
		ControlledPawn->AddMovementInput(RightDirection, MoveValue.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit) {
		return;
	}

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	/**
	* Line trace from custor to actor
	* A. LastActor is null && ThisActor is null
	*  - Do Nothing
	* B. LastActor is null && ThisActor is not null
	*  - Highlight ThisActor
	* C. LastActor is not null && ThisActor is null
	*  - Unhighlight LastActor
	* D. LastActor is not null && ThisActor is not null
	*  - Unhighlight LastActor
	*  - Highlight ThisActor
	*/

	// Case A
	if (LastActor == nullptr && ThisActor == nullptr) {
		return;
	}

	// Case B
	if (LastActor == nullptr && ThisActor != nullptr) {
		ThisActor->HighlightActor();
		return;
	}

	// Case C
	if (LastActor != nullptr && ThisActor == nullptr) {
		LastActor->UnhighlightActor();
		return;
	}

	// Case D
	if (LastActor != ThisActor) {
		LastActor->UnhighlightActor();
		ThisActor->HighlightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB)) {
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}

}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB)) {
		if (GetAuraAbilitySystemComponent()) {
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	// RMB is Pressed

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent()) {
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn<APawn>();

		if (FollowTime <= ShortPressThreshold && ControlledPawn) {
			
			if (auto* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination)) {
				if (NavigationPath->PathPoints.Num() > 1) {
					Spline->ClearSplinePoints();
					for (const FVector& Point : NavigationPath->PathPoints) {
						Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
						DrawDebugSphere(GetWorld(), Point, 50.f, 12, FColor::Green, false, 1.f);
					}

					CachedDestination = NavigationPath->PathPoints.Last();
					bAutoRunning = true;
				}
			}
		}

		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB)) {
		if (GetAuraAbilitySystemComponent()) {
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	// RMB is Pressed

	if (bTargeting) 
	{
		if (GetAuraAbilitySystemComponent()) {
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
			
		FHitResult Hit;

		if(GetHitResultUnderCursor(ECC_Visibility, false, Hit)) {
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn<APawn>()) {
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AbilitySystemComponent) {
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AbilitySystemComponent;
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) {
		return;
	}

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

		if (DistanceToDestination <= AutoRunAcceptanceRadius) {
			bAutoRunning = false;
		}
	}
}
