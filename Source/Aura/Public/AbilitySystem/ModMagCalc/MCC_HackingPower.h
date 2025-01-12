// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_HackingPower.generated.h"

/**
 * HackingPower Mod Calculation
 */
UCLASS()
class AURA_API UMCC_HackingPower : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_HackingPower();

protected:
    FGameplayEffectAttributeCaptureDefinition IntellectDef;
    FGameplayEffectAttributeCaptureDefinition CyberAffinityDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float IntellectCoefficient = 1.2f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float CyberAffinityCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 5.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 2.0f;
};
