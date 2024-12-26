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
#include <Character/AuraCharacterBase.h>

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

	AuraCharacter = Cast<AAuraCharacterBase>(GetPawn<APawn>());

	if (IsLocalController() && GEngine)
	{
		// ConsoleCommand(TEXT("showdebug abilitysystem"), true);
	}
	
	check(AuraContext);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}
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
	AuraInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Jump);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}


/*
 * Input Functions and State Machine
 */

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MoveValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AuraCharacter->AddMovementInput(ForwardDirection, MoveValue.Y);
	AuraCharacter->AddMovementInput(RightDirection, MoveValue.X);
}

void AAuraPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	AuraCharacter->Jump();
}

void AAuraPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// Camera

		FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

		FRotator CameraTargetRotation = GetControlRotation();
		CameraTargetRotation.Yaw += LookAxisVector.X * Sensitivity;
		CameraTargetRotation.Pitch = FMath::Clamp(CameraTargetRotation.Pitch - LookAxisVector.Y * Sensitivity, -80.0f, 80.0f);

		ForwardVector = FRotationMatrix(CameraTargetRotation).GetUnitAxis(EAxis::X);

		FRotator SmoothedCameraRotation = FMath::RInterpTo(GetControlRotation(), CameraTargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
		SetControlRotation(SmoothedCameraRotation);

		// Character
		// Only rotate the character if they are not idle
		if (!AuraCharacter->GetMovementComponent()->Velocity.IsNearlyZero()) {
			FRotator CharacterTargetRotation = ControlledPawn->GetActorRotation();
			CharacterTargetRotation.Yaw += LookAxisVector.X * Sensitivity;

			FRotator SmoothedCharacterRotation = FMath::RInterpTo(ControlledPawn->GetActorRotation(), CharacterTargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);

			ControlledPawn->SetActorRelativeRotation(SmoothedCharacterRotation);
		}
	}
}

/*
 * Abilities
 */

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

/*
 * Cursor Hits
 */

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
