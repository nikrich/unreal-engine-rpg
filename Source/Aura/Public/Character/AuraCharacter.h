// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include <Traversal/TraversalComponent.h>
#include "AuraCharacter.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interfact **/
	virtual int32 GetPlayerLevel() override;

	virtual FVector GetForwardVector() const override;
	/** End Combat Interfact **/

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGait Gait = EGait::Run;

	void ResetGait();
	void SetGaitFromDistance(float Distance);

private:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditDefaultsOnly)
	EGait DefaultGait = EGait::Run;

	UPROPERTY(EditDefaultsOnly)
	float MinSprintDistance = 1500.f;

	UPROPERTY(EditDefaultsOnly)
	float MinRunDistance = 800.f;
};
