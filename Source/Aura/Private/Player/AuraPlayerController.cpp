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
#include "GameFramework/CharacterMovementComponent.h"
#include <Character/AuraCharacter.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

/**
 * Constructor for the AuraPlayerController class.
 * Sets the bReplicates flag to true.
 */
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	PreviouslyHiddenActors = TArray<AActor*>();
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	LineTrace();
	RestoreVisibility();
	CameraTrace();
	AutoRun();
	DoCameraRotation(DeltaTime);
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

	AuraCharacter = Cast<AAuraCharacter>(GetPawn<APawn>());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
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

	AuraInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAuraPlayerController::Jump);
	AuraInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AAuraPlayerController::Sprint);
	AuraInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Started, this, &AAuraPlayerController::RotateCameraStart);
	AuraInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Completed, this, &AAuraPlayerController::RotateCameraEnd);
	AuraInputComponent->BindAction(ZoomCameraAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::ZoomCamera);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}


void AAuraPlayerController::RotateCameraStart(const FInputActionValue& Value)
{
	bIsRotatingCamera = true;
	GetMousePosition(LastMousePosition.X, LastMousePosition.Y);
}

void AAuraPlayerController::RotateCameraEnd(const FInputActionValue& Value)
{
	bIsRotatingCamera = false;
	CurrentYawSpeed = 0.0f; // Stop when mouse is released
}

void AAuraPlayerController::ZoomCamera(const FInputActionValue& Value)
{
	float ScrollDelta = Value.Get<float>();

	if (AAuraCharacter* AuraChar = Cast<AAuraCharacter>(GetPawn()))
	{
		USpringArmComponent* SpringArm = AuraChar->GetCameraBoom();
		if (SpringArm)
		{
			float NewTargetLength = SpringArm->TargetArmLength - ScrollDelta * ZoomSpeed;
			SpringArm->TargetArmLength = FMath::Clamp(NewTargetLength, MaxZoom, MinZoom);
		}
	}
}

void AAuraPlayerController::DoCameraRotation(float DeltaTime)
{
	if (!bIsRotatingCamera) return;

	FVector2D CurrentMousePos;
	GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);

	float MouseDeltaX = CurrentMousePos.X - LastMousePosition.X;
	float MouseDeltaY = CurrentMousePos.Y - LastMousePosition.Y;

	// Convert to speed: pixels/frame → degrees/second
	float MouseYawSpeed = MouseDeltaX * RotationYawSpeed;
	float MousePitchSpeed = MouseDeltaY * RotationPitchSpeed;

	if (bInvertPitchRotation) {
		MousePitchSpeed *= -1.f;
	}

	CurrentYawSpeed = FMath::Clamp(MouseYawSpeed, -MaxRotationSpeed, MaxRotationSpeed);
	CurrentPitchSpeed = FMath::Clamp(MousePitchSpeed, -MaxRotationSpeed, MaxRotationSpeed);

	// Apply yaw rotation
	if (AAuraCharacter* AuraChar = Cast<AAuraCharacter>(GetPawn()))
	{
		if (USpringArmComponent* SpringArm = AuraChar->GetCameraBoom())
		{
			FRotator CurrentRot = SpringArm->GetRelativeRotation();
			CurrentRot.Yaw += CurrentYawSpeed * DeltaTime;
			CurrentRot.Pitch = FMath::Clamp(CurrentRot.Pitch + CurrentPitchSpeed * DeltaTime, MinPitchRotation, MaxPitchRotation); // Clamp pitch to avoid flipping
			SpringArm->SetRelativeRotation(CurrentRot);
		}
	}

	// Gradually decay speed if mouse isn't moving
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, 0.0f, DeltaTime, RotationDecayRate);
}

void AAuraPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	AuraCharacter->Jump();
}

void AAuraPlayerController::Sprint(const FInputActionValue& InputActionValue)
{
	
}

/*
 * Abilities
 */

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// When ability is used, cancel running
	bAutoRunning = false;

	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		bTargeting = ThisActor ? true : false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		if (AAuraCharacter* ControlledPawn = Cast<AAuraCharacter>(GetPawn()))
		{
			if (FollowTime <= ShortPressThreshold)
			{
				if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
				{
					if (NavPath->PathPoints.Num() != 0)
					{
						Spline->ClearSplinePoints();
						for (const FVector& PointLoc : NavPath->PathPoints)
						{
							Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);

						}

						auto MovementDistance = Spline->GetSplineLength();
						// Set Gait based on how far the player needs to travel
						ControlledPawn->SetGaitFromDistance(MovementDistance);

						CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];

						// Emit Niagara effect at the destination
						check(NiagaraMoveToEmitter);

						UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							NiagaraMoveToEmitter,
							CachedDestination,
							FRotator::ZeroRotator,
							FVector(1.0f),
							true,
							true
						);

						bAutoRunning = true;
					}
				}
			}

			FollowTime = 0.f;
			bTargeting = false;
		}
	}

	if (GetAuraAbilitySystemComponent()) {
		GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}

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

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (AAuraCharacter* ControlledPawn = Cast<AAuraCharacter>(GetPawn()))
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
			ControlledPawn->ResetGait();
		}
	}
}

/*
 * Cursor Hits
 */

void AAuraPlayerController::LineTrace()
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

/**
 * Performs a camera trace from the character's camera to the player's.
 */
void AAuraPlayerController::CameraTrace()
{
	if (AuraCharacter->GetFollowCamera()) 
	{
		FVector CameraLocation = AuraCharacter->GetFollowCamera()->GetComponentLocation();
		FVector PlayerLocation = AuraCharacter->GetActorLocation(); 
		
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this); // Ignore the player
		Params.bReturnPhysicalMaterial = false;
		float Radius = 15.0f;

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			CameraLocation,
			PlayerLocation,
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeSphere(Radius),
			Params
		);

		if (bHit && HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();
			PreviouslyHiddenActors.AddUnique(HitActor);
			//HitActor->SetActorHiddenInGame(true); // Hard toggle
			// Disable Collisions
			//HitActor->SetActorEnableCollision(false);
		}
	}
}

void AAuraPlayerController::RestoreVisibility()
{
	for (AActor* Actor : PreviouslyHiddenActors)
	{
		if (IsValid(Actor))
		{
			Actor->SetActorHiddenInGame(false);
			// Re-enable Collisions
			Actor->SetActorEnableCollision(true);
		}
	}
	PreviouslyHiddenActors.Empty();
}
