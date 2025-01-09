// Copyright Hungry Ghost


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include <AuraGameplayTags.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include "AbilitySystem/AuraAttributeSet.h"
#include <Character/AuraCharacterBase.h>
#include <AuraAbilityTypes.h>

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Stamina);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_ArmorRating);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Evasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Accuracy);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_CriticalChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_CriticalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_HackingPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Persuasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_Stealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_MaxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Secondary_MaxEnergy);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Ballistic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Energy);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Kinetic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Piercing);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Toxic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Radiation);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Shock);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Digital);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Viral);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Sonic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Psychological);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Nanite);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Acid);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Biological);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_CriticalHit);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefinitions;

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Stamina, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_ArmorRating, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Evasion, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Accuracy, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_CriticalDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_HackingPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Persuasion, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_Stealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_MaxHealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Secondary_MaxEnergy, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Fire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Ballistic, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Energy, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Kinetic, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Piercing, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Toxic, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Radiation, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Shock, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Digital, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Viral, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Sonic, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Psychological, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Nanite, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Acid, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Biological, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_CriticalHit, Target, false);

		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

		UE_LOG(LogTemp, Warning, TEXT("Tags: %s"), *Tags.Attributes_Primary_Body.ToString());

		TagsToCaptureDefinitions.Add(Tags.Attributes_Stamina, Secondary_StaminaDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_ArmorRating, Secondary_ArmorRatingDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_ArmorPenetration, Secondary_ArmorPenetrationDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Evasion, Secondary_EvasionDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Accuracy, Secondary_AccuracyDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_CriticalChance, Secondary_CriticalChanceDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_CriticalDamage, Secondary_CriticalDamageDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_HackingPower, Secondary_HackingPowerDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Persuasion, Secondary_PersuasionDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Stealth, Secondary_StealthDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_MaxHealth, Secondary_MaxHealthDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_MaxEnergy, Secondary_MaxEnergyDef);

		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Fire, Resistance_FireDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Ballistic, Resistance_BallisticDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Energy, Resistance_EnergyDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Kinetic, Resistance_KineticDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Piercing, Resistance_PiercingDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Toxic, Resistance_ToxicDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Radiation, Resistance_RadiationDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Shock, Resistance_ShockDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Digital, Resistance_DigitalDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Viral, Resistance_ViralDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Sonic, Resistance_SonicDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Psychological, Resistance_PsychologicalDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Nanite, Resistance_NaniteDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Acid, Resistance_AcidDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_Resistances_Biological, Resistance_BiologicalDef);
		TagsToCaptureDefinitions.Add(Tags.Attributes_CriticalHitResistance, Resistance_CriticalHitDef);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_StaminaDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_ArmorRatingDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_EvasionDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_AccuracyDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_CriticalChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_CriticalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_HackingPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_PersuasionDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_StealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_MaxHealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().Secondary_MaxEnergyDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_CriticalHitDef);

	RelevantAttributesToCapture.Add(DamageStatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_BallisticDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_EnergyDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_KineticDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_PiercingDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ToxicDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_RadiationDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ShockDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_DigitalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ViralDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_SonicDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_PsychologicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_NaniteDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_AcidDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_BiologicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_CriticalHitDef);
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

	/*
	 * Look up Resistance Tags and calculate the damage reduction based on the resistance value.
	 */
	
	float Damage = 0.f;

	for (const auto& DamageTypePair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = DamageTypePair.Key;
		const FGameplayTag ResistanceTag = DamageTypePair.Value;

		const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& TagsToCaptureDefinitions = DamageStatics().TagsToCaptureDefinitions;

		// Debug
		
		for (const auto& Tag : TagsToCaptureDefinitions)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tag: %s"), *Tag.Key.ToString());
		}

		/*checkf(TagsToCaptureDefinitions.Contains(ResistanceTag), TEXT("Invalid Resistance Tag in DamageTypesToResistances"));
		const FGameplayEffectAttributeCaptureDefinition ResistanceCaptureDef = TagsToCaptureDefinitions[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypePair.Key);

		float ResistanceValue = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceCaptureDef, EvaluationParameters, ResistanceValue);
		ResistanceValue = FMath::Clamp(ResistanceValue, 0.f, 100.f);

		DamageTypeValue *= (100.f - ResistanceValue) / 100.f;
		
		Damage += DamageTypeValue;*/
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
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_CriticalHitDef, EvaluationParameters, TargetCriticalHitResistance);
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
