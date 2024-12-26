// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAnimMontage* GetHitReactMontage_Implementation() override { return HitReactMontage; }

	virtual void Die(FVector ImpactVector, bool bBlocked, bool bCriticalHit) override;

	virtual FVector GetForwardVector() const override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(FVector ImpactVector, bool bBlocked, bool bCriticalHit);

	// Movement
	UFUNCTION(BlueprintCallable)
	bool GetIsIdle() const { return bIsIdle; };

	UFUNCTION(BlueprintCallable)
	bool GetIsRunning() const { return bIsRunning; };

	UFUNCTION(BlueprintCallable)
	bool GetIsSprinting() const { return bIsSprinting; };

	UFUNCTION(BlueprintCallable)
	bool GetIsJumping() const { return bIsJumping; };

	UFUNCTION(BlueprintCallable)
	bool GetHasLanded() const { return bHasLanded; };

	UFUNCTION(BlueprintCallable)
	bool GetHasStartedToRun() const { return bHasStartedToRun; };

	void SetIsIdle(bool IsIdle);
	void SetIsRunning(bool IsRunning);
	void SetIsSprinting(bool IsSprinting);
	void SetIsJumping(bool IsJumping);
	void SetHasLanded(bool HasLanded);
	void SetHasStartedToRun(bool HasStartedToRun);


protected:
	virtual void BeginPlay() override;

	/*
	 * State Machine
	 */

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsIdle = true;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsStartingToRun = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsRunning = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsSprinting = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsJumping = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bIsCrouching = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bHasLanded = false;

	UPROPERTY(EditAnyWhere, Category = "Movement")
	bool bHasStartedToRun = false;

	UPROPERTY(EditAnyWhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	FName WeaponSocketName;

	virtual FVector GetCombatSocketLocation() const;

	UPROPERTY(BlueprintReadonly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadonly)
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalyAttributes;

	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	// Dissolve Effects
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Dissolve")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Dissolve")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);


private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<USoundBase> DeathSoundNormal;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<USoundBase> DeathSoundCriticalHit;
};
