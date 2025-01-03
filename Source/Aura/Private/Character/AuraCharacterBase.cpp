// Copyright Hungry Ghost


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "Components/CapsuleComponent.h"
#include <Aura/Aura.h>
#include <Kismet/GameplayStatics.h>
#include <Traversal/TraversalComponent.h>

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	// Create the Weapon component and attach it to the RootComponent of the character
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("Muzzle_01"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Add Traversal Component
	TraversalComponent = CreateDefaultSubobject<UTraversalComponent>("Traversal");
	TraversalComponent->SetupAttachment(GetMesh(), FName("Traversal Component"));

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::Die(FVector ImpactVector, bool bBlocked, bool bCriticalHit)
{
	if (Weapon) {
		Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}

	MulticastHandleDeath(ImpactVector, bBlocked, bCriticalHit);
}

FVector AAuraCharacterBase::GetForwardVector() const
{
	return FVector();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation(FVector ImpactVector, bool bBlocked, bool bCriticalHit)
{
	if (Weapon) {
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
	}

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	// Calculate the force of the impact based on the type of hit
	// If the hit was blocked, the force is halved
	// If the hit was a critical hit, the force is doubled

	float ForceMagnitude = 200000;
	ForceMagnitude *= bBlocked ? 0.5f : 1.f;
	ForceMagnitude *= bCriticalHit ? 2.f : 1.f;

	FVector VectorForce = ImpactVector * ForceMagnitude;
	GetMesh()->AddImpulse(VectorForce);

	// Play Death Sound
	// If the hit was a critical hit, play the critical hit sound

	if(bCriticalHit)
	{
		if (DeathSoundCriticalHit) UGameplayStatics::PlaySoundAtLocation(this, DeathSoundCriticalHit, GetActorLocation());
	}
	else
	{
		if (DeathSoundNormal) UGameplayStatics::PlaySoundAtLocation(this, DeathSoundNormal, GetActorLocation());
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

/*
 * Movement End
 */

FVector AAuraCharacterBase::GetCombatSocketLocation() const
{
	return GetMesh()->GetSocketLocation(WeaponSocketName);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::Jump()
{
	Super::Jump();
	TraversalComponent->PerformTraversalTrace();
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalyAttributes, 1.f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());

	if (!HasAuthority()) return;

	AuraAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void AAuraCharacterBase::Dissolve()
{
	// Character
	if (IsValid(DissolveMaterialInstance)) 
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);

		for (int32 i = 0; i < GetMesh()->GetMaterials().Max(); i++) 
		{
			GetMesh()->SetMaterial(i, DynamicMatInst);
		}

		StartDissolveTimeline(DynamicMatInst);
	}

	// Character Weapon
	if (!Weapon) return;

	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);

		for (int32 i = 0; i < GetMesh()->GetMaterials().Max(); i++)
		{
			Weapon->SetMaterial(i, DynamicMatInst);
		}

		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}
