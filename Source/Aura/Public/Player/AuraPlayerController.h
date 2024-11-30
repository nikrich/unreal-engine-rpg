/**
 * @file AuraPlayerController.h
 * @brief Contains the declaration of the AAuraPlayerController class.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;

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
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	/**
	  * @brief Handles the movement action.
	  * @param InputActionValue The input action value.
	  */
	void Move(const struct FInputActionValue& InputActionValue);

	void CursorTrace();

	 TScriptInterface<IEnemyInterface> LastActor;
	 TScriptInterface<IEnemyInterface> ThisActor;
};
