// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "AuraProjectile.generated.h"

DECLARE_DELEGATE_FiveParams(FEndAbilitySignature, FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, FGameplayAbilityActivationInfo, bool, bool)

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Effects")
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Effects")
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Effects")
	FGameplayAbilityActorInfo AbilityActorInfo;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Effects")
	FGameplayAbilityActivationInfo AbilityActivationInfo;


	FEndAbilitySignature EndAbilityHandle;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeSpan = 5.f;

	bool bHit = false;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

};
