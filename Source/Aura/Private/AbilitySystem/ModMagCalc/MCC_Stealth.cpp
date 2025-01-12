// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_Stealth.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_Stealth::UMCC_Stealth()
{
    // Capture the Agility attribute
    AgilityDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_AgilityAttribute();
    AgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AgilityDef.bSnapshot = false;

    // Capture the Perception attribute
    PerceptionDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_PerceptionAttribute();
    PerceptionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PerceptionDef.bSnapshot = false;

    // Add the attributes to be captured
    RelevantAttributesToCapture.Add(AgilityDef);
    RelevantAttributesToCapture.Add(PerceptionDef);
}

float UMCC_Stealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute values
    float AgilityValue = 0.0f;
    float PerceptionValue = 0.0f;

    GetCapturedAttributeMagnitude(AgilityDef, Spec, EvaluationParameters, AgilityValue);
    AgilityValue = FMath::Max(AgilityValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(PerceptionDef, Spec, EvaluationParameters, PerceptionValue);
    PerceptionValue = FMath::Max(PerceptionValue, 0.0f);  // Ensure non-negative value

    // Calculate the base Stealth
    float Stealth = (AgilityValue * AgilityCoefficient) + (PerceptionValue * PerceptionCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    Stealth += PostMultiplyAdditive;

    // Optional: Clamp the final value
    Stealth = FMath::Clamp(Stealth, 0.0f, 100.0f);  // Arbitrary cap to prevent extreme values

    return Stealth;
}
