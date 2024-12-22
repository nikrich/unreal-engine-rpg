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
#include "GameFramework/Character.h"
#include "UI/Widget//DamageTextComponent.h"

/**
 * Constructor for the AuraPlayerController class.
 * Sets the bReplicates flag to true.
 */
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	LineTrace();
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharcter, bool isBlockingHit, bool bIsCriticalHit)
{
	if (IsValid(TargetCharcter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharcter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharcter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, isBlockingHit, bIsCriticalHit);

	}
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

	/*FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;*/
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
	AuraInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Look);
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

void AAuraPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

		FRotator TargetRotation = GetControlRotation();
		TargetRotation.Yaw += LookAxisVector.X * Sensitivity;
		TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch - LookAxisVector.Y * Sensitivity, -80.0f, 80.0f);

		ForwardVector = FRotationMatrix(TargetRotation).GetUnitAxis(EAxis::X);

		// Smoothly interpolate the rotation
		FRotator SmoothedRotation = FMath::RInterpTo(GetControlRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
		SetControlRotation(SmoothedRotation);
	}
}

void AAuraPlayerController::LineTrace()
{
	// Perform Line Trace for Forward Vector
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (ForwardVector * LineTraceDistance);

	// Draw Debug Line
	// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f, 0, 1.f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetPawn());
	QueryParams.AddIgnoredActor(this);

	// Perform Line Trace
	GetWorld()->LineTraceSingleByChannel(LineTraceHit, Start, End, ECC_Visibility, QueryParams);

	if (!LineTraceHit.bBlockingHit) {

		if (LastActor != nullptr) {
			LastActor->UnhighlightActor();
			LastActor = nullptr;
		}

		if (ThisActor != nullptr) {
			ThisActor->UnhighlightActor();
			ThisActor = nullptr;
		}

		return;
	}

	LastActor = ThisActor;
	ThisActor = LineTraceHit.GetActor();

	if (LastActor == nullptr && ThisActor == nullptr) {
		return;
	}

	if (LastActor == nullptr && ThisActor != nullptr) {
		ThisActor->HighlightActor();
		return;
	}

	if (LastActor != nullptr && ThisActor == nullptr) {
		LastActor->UnhighlightActor();
		return;
	}

	if (LastActor != ThisActor) {
		LastActor->UnhighlightActor();
		ThisActor->HighlightActor();
	}

	bTargeting = ThisActor ? true : false;
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetAuraAbilitySystemComponent()) {
		GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetAuraAbilitySystemComponent()) {
		GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AbilitySystemComponent) {
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AbilitySystemComponent;
}
