// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_ArmorRating.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMCC_ArmorRating : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_ArmorRating();

protected:
    FGameplayEffectAttributeCaptureDefinition BodyDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float BodyCoefficient = 0.75f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
	
};
