// Copyright Hungry Ghost


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include <Interaction/CombatInterface.h>
#include "Actor/AuraProjectile.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(FVector Destination)
{
	// Check if we are the server
	bool bIsServver = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServver) return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		// Calculate Diraction to Destination
		const FVector Direction = (Destination - SocketLocation).GetSafeNormal();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Direction.ToOrientationQuat());

		// TODO - Set the Projectile Rotation.

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(AuraProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO - Give the Projectile a Gameplay Effect Spec for causing Damage.


		Projectile->FinishSpawning(SpawnTransform);
	}
}
