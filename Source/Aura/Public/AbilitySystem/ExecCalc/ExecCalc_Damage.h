// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "ExecCalc_Damage.generated.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Stamina);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_ArmorRating);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Evasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Accuracy);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_CriticalChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_CriticalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_HackingPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Persuasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Stealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_MaxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_MaxEnergy);

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Stamina, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_ArmorRating, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Evasion, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Accuracy, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_CriticalHitResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_CriticalDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_HackingPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Persuasion, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Stealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_MaxHealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_MaxEnergy, Source, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
