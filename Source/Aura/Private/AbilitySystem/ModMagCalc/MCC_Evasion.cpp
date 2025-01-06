// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_Evasion.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_Evasion::UMCC_Evasion()
{
    // Capture the Agility attribute
    AgilityDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_AgilityAttribute();
    AgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AgilityDef.bSnapshot = false;

    // Add the attribute to be captured
    RelevantAttributesToCapture.Add(AgilityDef);
}

float UMCC_Evasion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute value
    float AgilityValue = 0.0f;
    GetCapturedAttributeMagnitude(AgilityDef, Spec, EvaluationParameters, AgilityValue);
    AgilityValue = FMath::Max(AgilityValue, 0.0f);  // Ensure non-negative value

    // Calculate the base Evasion
    float Evasion = (AgilityValue * AgilityCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    Evasion += PostMultiplyAdditive;

    // Optional: Clamp the final value
    Evasion = FMath::Clamp(Evasion, 0.0f, 100.0f);

    return Evasion;
}
