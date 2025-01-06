// Copyright Hungry Ghost


#include "AbilitySystem/ModMagCalc/MCC_Stamina.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMCC_Stamina::UMCC_Stamina()
{
	BodyDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_BodyAttribute();
	BodyDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	BodyDef.bSnapshot = false;

	WillpowerDef.AttributeToCapture = UAuraAttributeSet::GetPrimary_WillpowerAttribute();
	WillpowerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	WillpowerDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BodyDef);
	RelevantAttributesToCapture.Add(WillpowerDef);
}

float UMCC_Stamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from the source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Body = 0.f;
	GetCapturedAttributeMagnitude(BodyDef, Spec, EvaluationParameters, Body);
	Body = FMath::Max(Body, 0.f);

	float Willpower = 0.f;
	GetCapturedAttributeMagnitude(WillpowerDef, Spec, EvaluationParameters, Willpower);
	Willpower = FMath::Max(Willpower, 0.f);

	return (Body * BodyCoefficient) + (Willpower * WillpowerCoefficient);
}
