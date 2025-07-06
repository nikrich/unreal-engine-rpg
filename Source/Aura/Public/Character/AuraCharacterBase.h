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
class UTraversalComponent;

UENUM(BlueprintType)
enum class EGait : uint8
{
	Walk,
	Run,
	Sprint
};

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

	virtual void Jump() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGait Gait = EGait::Run;

	/*
	 * Movement
	 */

	void ResetGait();
	void SetGaitFromDistance(float Distance);

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadonly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	FName WeaponSocketName;

	UPROPERTY(EditAnyWhere, BlueprintReadonly, Category = "Traversal")
	TObjectPtr<UTraversalComponent> TraversalComponent;

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
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultResistanceAttributes;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	/*
	 * Movement
	 */

	UPROPERTY(EditDefaultsOnly)
	EGait DefaultGait = EGait::Run;

	/*
	 * Dissolve Effects
	 */ 

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

	UPROPERTY(EditDefaultsOnly)
	float MinSprintDistance = 1500.f;

	UPROPERTY(EditDefaultsOnly)
	float MinRunDistance = 800.f;
};
