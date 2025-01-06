// Copyright Hungry Ghost


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include <AuraGameplayTags.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include <Character/AuraCharacterBase.h>
#include <AuraAbilityTypes.h>


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_StaminaDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_ArmorRatingDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_EvasionDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_AccuracyDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_CriticalChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_CriticalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_HackingPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_PersuasionDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_StealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_MaxHealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_MaxEnergyDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Boilerplace

	const UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	// Interfaces for Combat related functions
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	// Custom Effect Context

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContext);

	// Get Gameplay Tags

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	// Get Damage by Caller Magnitude
	float Damage = 0.f;

	for (const auto& DamageTypePair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypePair.Key);
		Damage += DamageTypeValue;
	}
	
	// Capture Blackchance on Target and Determine if there was a succesful block
	
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_EvasionDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Clamp(TargetBlockChance, 0.f, 100.f);
	
	bool bBlocked =  FMath::RandRange(0.f, 100.f) <= TargetBlockChance;
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	// If Block then reduce damage by half

	Damage = bBlocked ? Damage / 2 : Damage = Damage;

	// Armor - Reduces the damage of a hit

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_ArmorRatingDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Clamp(TargetArmor, 0.f, 100.f);

	// Armor Penetration - a percentage of the Target's Armor that is ignored

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Clamp(SourceArmorPenetration, 0.f, 100.f);

	FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoeffients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveArmor = TargetArmor * (100.f - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	// Effective Armor - Damage ignores a percentage of the Target's Armor

	FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoeffients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	Damage *= (100.f - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	// Critical Hit - Increases the damage of a hit

	float SourceCriticalHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_CriticalChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Clamp(SourceCriticalHitChance, 0.f, 100.f);

	float TargetCriticalHitResistance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_CriticalHitResistanceDef, EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Clamp(TargetCriticalHitResistance, 0.f, 100.f);

	float SourceCriticalHitDamage = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Secondary_CriticalDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Clamp(SourceCriticalHitDamage, 0.f, 100.f);

	FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoeffients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	const float EffectiveHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	bool bIsCriticalHit = FMath::RandRange(0.f, 100.f) <= EffectiveHitChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);

	Damage = bIsCriticalHit ? Damage * 2 + SourceCriticalHitDamage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
