// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_CriticalDamage.generated.h"

/**
 * CriticalDamage Mod Calculation
 */
UCLASS()
class AURA_API UMCC_CriticalDamage : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_CriticalDamage();

protected:
    FGameplayEffectAttributeCaptureDefinition BodyDef;
    FGameplayEffectAttributeCaptureDefinition PerceptionDef;
    FGameplayEffectAttributeCaptureDefinition LuckDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float BodyCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PerceptionCoefficient = 0.6f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float LuckCoefficient = 0.4f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 5.0f;
};
