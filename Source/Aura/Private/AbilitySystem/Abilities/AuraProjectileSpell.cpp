// Copyright Hungry Ghost


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include <Interaction/CombatInterface.h>
#include "Actor/AuraProjectile.h"
#include <AbilitySystemComponent.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <AuraGameplayTags.h>

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

AAuraProjectile* UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Check if we are the server
	bool bIsServver = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServver) return nullptr;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(AuraProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		
		// Create Effect Context

		FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);

		// End Create Effect Context

		const FGameplayEffectSpecHandle SpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
		const FGameplayAbilitySpecHandle AbilityHandle = GetCurrentAbilitySpecHandle();

		// Set Meta Data on Projectile in order to apply damage
		// and to end the ability when the projectile hits something
		Projectile->DamageEffectSpecHandle = SpecHandle;
		Projectile->AbilitySpecHandle = AbilityHandle;
		Projectile->AbilityActorInfo = GetActorInfo();
		Projectile->AbilityActivationInfo = CurrentActivationInfo;
		Projectile->EndAbilityHandle.BindUObject(this, &UAuraProjectileSpell::EndAbility);

		// Add Damage to SpecHandle
		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

		for (const auto& DamageType : DamageTypes)
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageType.Key, DamageType.Value.GetValueAtLevel(GetAbilityLevel()));
		}

		Projectile->FinishSpawning(SpawnTransform);
		return Projectile;
	}

	return nullptr;
}
