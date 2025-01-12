// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_Stealth.generated.h"

/**
 * Stealth Mod Calculation
 */
UCLASS()
class AURA_API UMCC_Stealth : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_Stealth();

protected:
    FGameplayEffectAttributeCaptureDefinition AgilityDef;
    FGameplayEffectAttributeCaptureDefinition PerceptionDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float AgilityCoefficient = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PerceptionCoefficient = 0.6f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
};
