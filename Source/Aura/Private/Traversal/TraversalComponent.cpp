// Copyright Hungry Ghost


#include "Traversal/TraversalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Traversal/TraversableBlock.h>

UTraversalComponent::UTraversalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTraversalComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());
	CapsuleRadius= Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	CapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
}

void UTraversalComponent::TryTraversalAction()
{
	const FTraceResult TraceResult = PerformTrace();
}

FTraversalInputType UTraversalComponent::GetTraversalInput() const
{
	// Gets how fast the character is moving in its forward direction and uses the value to scale the distance of the forward trace.
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	EMovementMode MovementMode = MovementComponent->MovementMode;
	FVector Velocity = MovementComponent->Velocity;
	FVector UnrotatedVelocity = Character->GetActorRotation().UnrotateVector(Velocity);
	float UnrotatedMapClampedVelocity = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 500.0f), FVector2D(75.f, 350.f), UnrotatedVelocity.X);
	FVector ForwardVector = Character->GetActorForwardVector();

	// TODO - Add back when done with refactor
	//// Don't traverse if the character is falling or flying.
	//if (MovementMode == EMovementMode::MOVE_Falling || MovementMode == EMovementMode::MOVE_Flying) 
	//{
	//	return FTraversalInputType(ForwardVector, 0.0f, FVector(), FVector(), 0.0f, 0.0f);
	//}

	// These trace values are hardcoded for now, but will be replaced with variables that can be set in the editor.
	return FTraversalInputType(ForwardVector, UnrotatedMapClampedVelocity, FVector(0.f, 0.f, 50.f), FVector(0.f, 0.f, 50.f), 30.0f, 60.f);
}

FTraceResult UTraversalComponent::PerformTrace() const
{
	const FTraversalInputType TraversalInput = GetTraversalInput();
	const FVector CharacterLocation = Character->GetActorLocation();

	FVector StartSweepLocation = CharacterLocation + TraversalInput.TraceOriginOffset;
	FVector EndSweepLocation = TraversalInput.TraceEndOffset + (TraversalInput.TraceForwardVector * TraversalInput.TraceForwardDistance) + CharacterLocation;

	if (DrawDebug) 
	{
		DrawDebugLine(GetWorld(), StartSweepLocation, EndSweepLocation, FColor::Green, false, 2.f);
	}

	// Capsule Trace by Channel
	FHitResult HitResult;
	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, StartSweepLocation, EndSweepLocation, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), FCollisionQueryParams(FName(TEXT("")), false, Character));

	// Traversal Check Failed - Return Check Failed with FTraceResult Struct
	if (!bTraceSuccess)
	{
		return FTraceResult(true, false);
	}

	// Hit Has Occurred

	AActor* HitActor = HitResult.GetActor();
	ATraversableBlock* TraversableBlock = Cast<ATraversableBlock>(HitActor);

	FTraversalCheckResult TraversalCheckResult = FTraversalCheckResult();
	TraversalCheckResult.HitComponent = HitResult.GetComponent();

	TraversableBlock->GetLedgeTransforms(HitResult.ImpactPoint, CharacterLocation, TraversalCheckResult);

	if (!TraversalCheckResult.bHasFrontLedge) {
		return FTraceResult(true, false);
	}



	return FTraceResult(true, false);
}

