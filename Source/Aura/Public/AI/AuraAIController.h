// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAuraAIController();
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bDebug = false;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void CalculatePath(FVector Location);

private:
	FVector CachedDestination = FVector::ZeroVector;
	bool bAutoRunning = false;

	UPROPERTY(EditDefaultsOnly)
	float MeleeAutoRunAcceptanceRadius = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float RangedAutoRunAcceptanceRadius = 400.f;

	float GetAutoRunAcceptanceRadius() const;

};
