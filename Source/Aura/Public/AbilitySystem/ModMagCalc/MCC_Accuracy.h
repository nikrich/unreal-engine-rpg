// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_Accuracy.generated.h"

/**
 * Accuracy Mod Calculation
 */
UCLASS()
class AURA_API UMCC_Accuracy : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_Accuracy();

protected:
    FGameplayEffectAttributeCaptureDefinition PerceptionDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PerceptionCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 5.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
};
