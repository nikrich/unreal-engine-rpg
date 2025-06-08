// Copyright Hungry Ghost


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (!TargetAbilitySystemComponent) return;

	for (auto& GameplayEffectClass : GameplayEffectClasses)
	{
		checkf(GameplayEffectClass, TEXT("GameplayEffectClass is null in AAuraEffectActor::ApplyEffectToTarget"));
		FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

		if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
		}

		if (!bIsInfinite) {
			Destroy();
		}
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (!IsValid(TargetAbilitySystemComponent)) return;

		TArray<FActiveGameplayEffectHandle> ActiveEffectHandlesToRemove;

		for (auto& ActiveEffectHandle : ActiveEffectHandles)
		{
			if (ActiveEffectHandle.Value == TargetAbilitySystemComponent)
			{
				TargetAbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
				ActiveEffectHandlesToRemove.Add(ActiveEffectHandle.Key);
			}
		}

		for (auto& ActiveEffectHandleToRemove : ActiveEffectHandlesToRemove)
		{
			ActiveEffectHandles.Remove(ActiveEffectHandleToRemove);
		}
	}
}


