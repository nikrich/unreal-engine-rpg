// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MCC_ArmorPenetration.generated.h"

/**
 * ArmorPenetration Mod Calculation
 */
UCLASS()
class AURA_API UMCC_ArmorPenetration : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    UMCC_ArmorPenetration();

protected:
    FGameplayEffectAttributeCaptureDefinition AgilityDef;

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float AgilityCoefficient = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PreMultiplyAdditive = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Coefficients")
    float PostMultiplyAdditive = 0.5f;
};
