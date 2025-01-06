// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_CriticalChance.generated.h"

/**
 * CriticalChance Mod Calculation
 */
UCLASS()
class AURA_API UMCC_CriticalChance : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_CriticalChance();

protected:
    FGameplayEffectAttributeCaptureDefinition PerceptionDef;
    FGameplayEffectAttributeCaptureDefinition LuckDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PerceptionCoefficient = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float LuckCoefficient = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 1.0f;
};
