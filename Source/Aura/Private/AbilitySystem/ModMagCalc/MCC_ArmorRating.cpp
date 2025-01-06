// Copyright Hungry Ghost


#include "AbilitySystem/ModMagCalc/MCC_ArmorRating.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_ArmorRating::UMCC_ArmorRating()
{
    // Capture the Body attribute
    BodyDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_BodyAttribute();
    BodyDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    BodyDef.bSnapshot = false;

    // Add the attribute to be captured
    RelevantAttributesToCapture.Add(BodyDef);
}

float UMCC_ArmorRating::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute value
    float BodyValue = 0.0f;
    GetCapturedAttributeMagnitude(BodyDef, Spec, EvaluationParameters, BodyValue);
    BodyValue = FMath::Max(BodyValue, 0.0f);  // Ensure non-negative value

    // Calculate the base ArmorRating
    float ArmorRating = (BodyValue * BodyCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    ArmorRating += PostMultiplyAdditive;

    return ArmorRating;
}