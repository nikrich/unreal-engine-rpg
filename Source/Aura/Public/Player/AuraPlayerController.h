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
	class AAuraCharacterBase* AuraCharacter;

	/*
	 * Input Actions
	 */

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveActionController;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookActionController;

	UPROPERTY(EditAnywhere, Category = "Input")
	float Sensitivity = 5.f;

	UPROPERTY(EditAnywhere, Category = "Input")
	float ControllerSensitivity = 5.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeadZone = 0.2f;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	FVector ForwardVector;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	float LineTraceDistance = 2000.f;

	/*
	 * Input Functions
	 */

	void MoveStarted(const struct FInputActionValue& InputActionValue);
	void MoveEnded(const struct FInputActionValue& InputActionValue);
	void Move(const struct FInputActionValue& InputActionValue);

	void CrouchStarted(const struct FInputActionValue& InputActionValue);
	void CrouchEnded(const struct FInputActionValue& InputActionValue);
	void Crouch(const struct FInputActionValue& InputActionValue);

	void Jump(const struct FInputActionValue& InputActionValue);
	void StopJumping(const struct FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& Value);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void HasStartedToRun();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/*
	 * Cursor Hits
	 */

	void LineTrace();
	FHitResult LineTraceHit;

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	bool bTargeting = false;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Damage Text")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
