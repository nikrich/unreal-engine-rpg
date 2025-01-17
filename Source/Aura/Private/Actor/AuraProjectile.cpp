// Copyright Hungry Ghost


#include "Actor/AuraProjectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Components/AudioComponent.h"
#include <Aura/Aura.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include <NiagaraFunctionLibrary.h>

// Sets default values
AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, RootComponent);
}

void AAuraProjectile::Destroyed()
{
	// If Client and the Server has not hit the projectile, play the impact sound and effect
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if(LoopingSoundComponent) LoopingSoundComponent->Stop();
	}

	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// See if the projectile hit the casting actor
	if (OtherActor == AbilityActorInfo.AvatarActor) {
		bHit = true;
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (LoopingSoundComponent) LoopingSoundComponent->Stop();

	// This is done to ensure that the projectile is destroyed on the server
	// We also make sure that the projectile is is destroyed correctly on the client by setting bHit to true
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor)) {
			auto MyAttributeSet = TargetAbilitySystemComponent->GetSet<UAuraAttributeSet>();
			TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		if (EndAbilityHandle.IsBound()) {
			EndAbilityHandle.Execute(AbilitySpecHandle, &AbilityActorInfo, AbilityActivationInfo, true, false);
		}

		Destroy();
	}
	else 
	{
		bHit = true;
	}
}
