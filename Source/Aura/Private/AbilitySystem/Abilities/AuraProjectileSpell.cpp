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

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Check if we are the server
	bool bIsServver = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServver) return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FVector Direction = (ProjectileTargetLocation - SocketLocation).GetSafeNormal();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.0f;

		UE_LOG(LogTemp, Warning, TEXT("SpawnProjectile: %s"), *Direction.ToString());
		
		// Offset used to avoid projectile colliding with own actor
		FVector Offset = Direction * ProjectileSpawnOffset;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation + Offset);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(AuraProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceAbilitySystemComponent->MakeEffectContext());
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
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, Damage.GetValueAtLevel(GetAbilityLevel()));

		Projectile->FinishSpawning(SpawnTransform);
	}
}
