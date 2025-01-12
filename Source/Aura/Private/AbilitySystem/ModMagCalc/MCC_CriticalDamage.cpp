// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_CriticalDamage.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_CriticalDamage::UMCC_CriticalDamage()
{
    // Capture the Body attribute
    BodyDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_BodyAttribute();
    BodyDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    BodyDef.bSnapshot = false;

    // Capture the Perception attribute
    PerceptionDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_PerceptionAttribute();
    PerceptionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PerceptionDef.bSnapshot = false;

    // Capture the Luck attribute
    LuckDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_LuckAttribute();
    LuckDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    LuckDef.bSnapshot = false;

    // Add the attributes to be captured
    RelevantAttributesToCapture.Add(BodyDef);
    RelevantAttributesToCapture.Add(PerceptionDef);
    RelevantAttributesToCapture.Add(LuckDef);
}

float UMCC_CriticalDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute values
    float BodyValue = 0.0f;
    float PerceptionValue = 0.0f;
    float LuckValue = 0.0f;

    GetCapturedAttributeMagnitude(BodyDef, Spec, EvaluationParameters, BodyValue);
    BodyValue = FMath::Max(BodyValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(PerceptionDef, Spec, EvaluationParameters, PerceptionValue);
    PerceptionValue = FMath::Max(PerceptionValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(LuckDef, Spec, EvaluationParameters, LuckValue);
    LuckValue = FMath::Max(LuckValue, 0.0f);  // Ensure non-negative value

    // Calculate the base CriticalDamage
    float CriticalDamage = (BodyValue * BodyCoefficient) + (PerceptionValue * PerceptionCoefficient) + (LuckValue * LuckCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    CriticalDamage += PostMultiplyAdditive;

    // Optional: Clamp the final value
    CriticalDamage = FMath::Clamp(CriticalDamage, 0.0f, 500.0f);  // Arbitrary cap to prevent extreme values

    return CriticalDamage;
}
