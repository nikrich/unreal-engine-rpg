/**
 * @file AuraPlayerController.h
 * @brief Contains the declaration of the AAuraPlayerController class.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;
class UDamageTextComponent;

 /**
  * @class AAuraPlayerController
  * @brief Represents the player controller for the Aura game.
  */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	* @brief Default constructor for AAuraPlayerController.
	*/
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharcter, bool isBlockingHit, bool bIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	FVector GetForwardVector() const { return ForwardVector; }

protected:
	/**
	  * @brief Called when the game starts or when spawned.
	  */
	virtual void BeginPlay() override;

	/**
	  * @brief Sets up the input component for the player controller.
	  */
	virtual void SetupInputComponent() override;

private:
	class AAuraCharacter* AuraCharacter;

	/*
	 * Inputs 
	 */

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> RotateCameraAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> ZoomCameraAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	float Sensitivity = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/*
	 * Effects
	 */

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<class UNiagaraSystem> NiagaraMoveToEmitter;

	/*
	 * Combat
	 */

	UPROPERTY(EditAnyWhere, Category = "Combat")
	FVector ForwardVector;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	float LineTraceDistance = 2000.f;

	/*
	 * Auto Run
	 */

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void HasStartedToRun();

	void AutoRun();

	/*
	 * Input Functions
	 */

	void Move(const struct FInputActionValue& InputActionValue);
	void RotateCameraStart(const FInputActionValue& Value);
	void RotateCameraEnd(const FInputActionValue& Value);
	void ZoomCamera(const FInputActionValue& Value);
	void Jump(const struct FInputActionValue& InputActionValue);
	void Sprint(const struct FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/*
	 * Camera
	 */

	bool bIsRotatingCamera = false;
	float CurrentYawSpeed = 0.0f;
	float CurrentPitchSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float MaxZoom = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float MinZoom = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float ZoomSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	bool bInvertPitchRotation = true;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float MaxPitchRotation = 90.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float MinPitchRotation = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float RotationDecayRate = 3.0f; // How fast rotation slows down

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float MaxRotationSpeed = 100.0f; // Degrees per second

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float RotationYawSpeed = 3.0f; // Degrees per second

	UPROPERTY(EditDefaultsOnly, Category = "Input - Camera Rotation")
	float RotationPitchSpeed = 1.0f; // Degrees per second

	FVector2D LastMousePosition;
	void DoCameraRotation(float DeltaTime);

	/*
	 * Cursor Hits
	 */

	void LineTrace();
	FHitResult LineTraceHit;

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Damage Text")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	/*
	 * Camera Visibility Trace
	 */

	void CameraTrace();
	TArray<AActor*> PreviouslyHiddenActors;
	void RestoreVisibility();
};
