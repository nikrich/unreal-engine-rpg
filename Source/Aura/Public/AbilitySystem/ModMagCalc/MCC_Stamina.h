// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_Stamina.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMCC_Stamina : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMCC_Stamina();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition BodyDef;
	FGameplayEffectAttributeCaptureDefinition WillpowerDef;
	
	UPROPERTY(EditAnywhere, Category = "Coefficients")
	float BodyCoefficient = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Coefficients")
	float WillpowerCoefficient = 0.8f;

};
