// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;

/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly , Category = "Projectile")
	float ProjectileSpawnOffset = 1.f;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AAuraProjectile> AuraProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Effects")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
