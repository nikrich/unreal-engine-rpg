// Copyright Hungry Ghost

#include "AbilitySystem/ModMagCalc/MCC_Accuracy.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_Accuracy::UMCC_Accuracy()
{
    // Capture the Perception attribute
    PerceptionDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_PerceptionAttribute();
    PerceptionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PerceptionDef.bSnapshot = false;

    // Add the attribute to be captured
    RelevantAttributesToCapture.Add(PerceptionDef);
}

float UMCC_Accuracy::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather the tags from the source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // Get captured attribute value
    float PerceptionValue = 0.0f;
    GetCapturedAttributeMagnitude(PerceptionDef, Spec, EvaluationParameters, PerceptionValue);
    PerceptionValue = FMath::Max(PerceptionValue, 0.0f);  // Ensure non-negative value

    // Calculate the base Accuracy
    float Accuracy = (PerceptionValue * PerceptionCoefficient) + PreMultiplyAdditive;

    // Apply post-multiply additive
    Accuracy += PostMultiplyAdditive;

    // Optional: Clamp the final value
    Accuracy = FMath::Clamp(Accuracy, 0.0f, 100.0f);

    return Accuracy;
}
