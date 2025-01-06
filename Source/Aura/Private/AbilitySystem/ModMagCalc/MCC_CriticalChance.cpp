// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_CriticalChance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_CriticalChance::UMCC_CriticalChance()
{
    // Capture the Perception attribute
    PerceptionDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_PerceptionAttribute();
    PerceptionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PerceptionDef.bSnapshot = false;

    // Capture the Luck attribute
    LuckDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_LuckAttribute();
    LuckDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    LuckDef.bSnapshot = false;

    // Add the attributes to be captured
    RelevantAttributesToCapture.Add(PerceptionDef);
    RelevantAttributesToCapture.Add(LuckDef);
}

float UMCC_CriticalChance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute values
    float PerceptionValue = 0.0f;
    float LuckValue = 0.0f;

    GetCapturedAttributeMagnitude(PerceptionDef, Spec, EvaluationParameters, PerceptionValue);
    PerceptionValue = FMath::Max(PerceptionValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(LuckDef, Spec, EvaluationParameters, LuckValue);
    LuckValue = FMath::Max(LuckValue, 0.0f);  // Ensure non-negative value

    // Calculate the base CriticalChance
    float CriticalChance = (PerceptionValue * PerceptionCoefficient) + (LuckValue * LuckCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    CriticalChance += PostMultiplyAdditive;

    // Optional: Clamp the final value
    CriticalChance = FMath::Clamp(CriticalChance, 0.0f, 100.0f);

    return CriticalChance;
}
