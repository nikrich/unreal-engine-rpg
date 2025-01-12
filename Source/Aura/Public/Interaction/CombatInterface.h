// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetForwardVector() const;

	virtual int32 GetPlayerLevel() { return 0; }
	virtual FVector GetCombatSocketLocation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
	void SetWarpingTarget(const FVector& FacingLocation);

	virtual void Die(FVector ImpactVector, bool bBlocked, bool bCriticalHit) = 0;
};
