// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class AuraAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8 {
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8 {
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	bool bDestroyOnEffectRemoval = false;

	// Apply / Remove Effects

	UFUNCTION(BlueprintCallable, Category = "Aura Effect")
	void ApplyEffectToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses);

	// Overlap Events

	UFUNCTION(BlueprintCallable, Category = "Aura Effect")
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Aura Effect")
	void OnEndOverlap(AActor* TargetActor);

	// Instant Effect

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	// Rather use array
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectRemovalPolicy InstantEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;


	// Duration Effect

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectRemovalPolicy DurationEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	// Infinite Effect

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	// Level

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Applied Effects")
	float ActorLevel = 1.f;

};
