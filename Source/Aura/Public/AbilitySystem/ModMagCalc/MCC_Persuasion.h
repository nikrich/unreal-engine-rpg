// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_Persuasion.generated.h"

/**
 * Persuasion Mod Calculation
 */
UCLASS()
class AURA_API UMCC_Persuasion : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_Persuasion();

protected:
    FGameplayEffectAttributeCaptureDefinition CharismaDef;
    FGameplayEffectAttributeCaptureDefinition LuckDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float CharismaCoefficient = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float LuckCoefficient = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
};
