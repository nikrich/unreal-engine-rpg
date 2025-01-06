// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_Evasion.generated.h"

/**
 * Evasion Mod Calculation
 */
UCLASS()
class AURA_API UMCC_Evasion : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_Evasion();

protected:
    FGameplayEffectAttributeCaptureDefinition AgilityDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float AgilityCoefficient = 0.6f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
};
