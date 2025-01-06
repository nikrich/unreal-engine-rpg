// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_HackingPower.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_HackingPower::UMCC_HackingPower()
{
    // Capture the Intellect attribute
    IntellectDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_IntellectAttribute();
    IntellectDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntellectDef.bSnapshot = false;

    // Capture the CyberAffinity attribute
    CyberAffinityDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_CyberAffinityAttribute();
    CyberAffinityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    CyberAffinityDef.bSnapshot = false;

    // Add the attributes to be captured
    RelevantAttributesToCapture.Add(IntellectDef);
    RelevantAttributesToCapture.Add(CyberAffinityDef);
}

float UMCC_HackingPower::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute values
    float IntellectValue = 0.0f;
    float CyberAffinityValue = 0.0f;

    GetCapturedAttributeMagnitude(IntellectDef, Spec, EvaluationParameters, IntellectValue);
    IntellectValue = FMath::Max(IntellectValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(CyberAffinityDef, Spec, EvaluationParameters, CyberAffinityValue);
    CyberAffinityValue = FMath::Max(CyberAffinityValue, 0.0f);  // Ensure non-negative value

    // Calculate the base HackingPower
    float HackingPower = (IntellectValue * IntellectCoefficient) + (CyberAffinityValue * CyberAffinityCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    HackingPower += PostMultiplyAdditive;

    // Optional: Clamp the final value
    HackingPower = FMath::Clamp(HackingPower, 0.0f, 500.0f);  // Arbitrary cap to prevent extreme values

    return HackingPower;
}
