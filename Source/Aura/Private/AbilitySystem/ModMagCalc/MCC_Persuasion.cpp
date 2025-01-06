// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_Persuasion.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_Persuasion::UMCC_Persuasion()
{
    // Capture the Charisma attribute
    CharismaDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_CharismaAttribute();
    CharismaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    CharismaDef.bSnapshot = false;

    // Capture the Luck attribute
    LuckDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_LuckAttribute();
    LuckDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    LuckDef.bSnapshot = false;

    // Add the attributes to be captured
    RelevantAttributesToCapture.Add(CharismaDef);
    RelevantAttributesToCapture.Add(LuckDef);
}

float UMCC_Persuasion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute values
    float CharismaValue = 0.0f;
    float LuckValue = 0.0f;

    GetCapturedAttributeMagnitude(CharismaDef, Spec, EvaluationParameters, CharismaValue);
    CharismaValue = FMath::Max(CharismaValue, 0.0f);  // Ensure non-negative value

    GetCapturedAttributeMagnitude(LuckDef, Spec, EvaluationParameters, LuckValue);
    LuckValue = FMath::Max(LuckValue, 0.0f);  // Ensure non-negative value

    // Calculate the base Persuasion
    float Persuasion = (CharismaValue * CharismaCoefficient) + (LuckValue * LuckCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    Persuasion += PostMultiplyAdditive;

    // Optional: Clamp the final value
    Persuasion = FMath::Clamp(Persuasion, 0.0f, 100.0f);  // Arbitrary cap to prevent extreme values

    return Persuasion;
}
