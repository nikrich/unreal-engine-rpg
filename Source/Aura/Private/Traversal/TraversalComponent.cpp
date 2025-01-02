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

	if (!TraversableBlock)
	{
		return FTraceResult(true, false);
	}

	FTraversalCheckResult TraversalCheckResult = FTraversalCheckResult();
	TraversalCheckResult.HitComponent = HitResult.GetComponent();

	TraversableBlock->GetLedgeTransforms(HitResult.ImpactPoint, CharacterLocation, TraversalCheckResult);

	if (!TraversalCheckResult.bHasFrontLedge) {
		return FTraceResult(true, false);
	}

	// Perform a trace from the actors location up to the front ledge location to determine 
	// if there is room for the actor to move up to it. If so, continue the function. If not, exit early.
	const FVector FrontLedgeLocationCollisionCheck = TraversalCheckResult.FrontLedgeLocation + (TraversalCheckResult.FrontLedgeNormal * CapsuleRadius + 2) + FVector(0.f, 0.f, CapsuleHalfHeight + 2.f);
	const bool bCanTraverseLedge = CheckTraceForFrontLedge(TraversalCheckResult, FrontLedgeLocationCollisionCheck).bBlockingHit;

	if (!bCanTraverseLedge)
	{
		return FTraceResult(true, false);
	}

	// Save the height of the obstacle using the delta between the actor and front ledge transform.
	TraversalCheckResult.ObstacleHeight = TraversalCheckResult.FrontLedgeLocation.Z - CharacterLocation.Z;

	// Perform a trace across the top of the obstacle from the front ledge to the back ledge to see if theres room for the actor to move across it.
	// If there is room, continue the function. If not, exit early.

	const FVector BackLedgeLocationCollisionCheck = TraversalCheckResult.BackLedgeLocation + (TraversalCheckResult.BackLedgeNormal * CapsuleRadius + 2) + FVector(0.f, 0.f, CapsuleHalfHeight + 2.f);
	const bool bIsBlockedFromRunningToBackLedge = CheckTraceForBackLedge(TraversalCheckResult, FrontLedgeLocationCollisionCheck, BackLedgeLocationCollisionCheck).bBlockingHit;
	
	if (bIsBlockedFromRunningToBackLedge)
	{
		TraversalCheckResult.bHasBackLedge = false;
	}
	else 
	{
		TraversalCheckResult.ObstacleDepth = FMath::Abs(FVector::Dist(TraversalCheckResult.FrontLedgeLocation, TraversalCheckResult.BackLedgeLocation));
	}

	// Print State of Traversal Check Result
	if (DrawDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("Front Ledge Location: %s"), *TraversalCheckResult.FrontLedgeLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Front Ledge Normal: %s"), *TraversalCheckResult.FrontLedgeNormal.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Back Ledge Location: %s"), *TraversalCheckResult.BackLedgeLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Back Ledge Normal: %s"), *TraversalCheckResult.BackLedgeNormal.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Obstacle Height: %f"), TraversalCheckResult.ObstacleHeight);
		UE_LOG(LogTemp, Warning, TEXT("Obstacle Depth: %f"), TraversalCheckResult.ObstacleDepth);
	}

	
	// Trace downward from the back ledge location (using the height of the obstacle for the distance) to find the floor. 
	// If there is a floor, save its location and the back ledges height (using the distance between the back ledge and the floor). 
	// If no floor was found, invalidate the back floor.
	 
	const FHitResult BackFloorCollisionCheck = CheckTraceForBackFloor(TraversalCheckResult, BackLedgeLocationCollisionCheck);
	const bool bHasBackFloor = BackFloorCollisionCheck.bBlockingHit;

	if (bHasBackFloor) 
	{
		TraversalCheckResult.bHasBackFloor = true;
		TraversalCheckResult.BackFloorLocation = BackFloorCollisionCheck.ImpactPoint;
		TraversalCheckResult.BackLedgeHeight = TraversalCheckResult.BackLedgeLocation.Z - TraversalCheckResult.BackFloorLocation.Z;
	}
	else
	{
		TraversalCheckResult.bHasBackFloor = false;
	}

	return FTraceResult(true, false);
}

FHitResult UTraversalComponent::CheckTraceForFrontLedge(FTraversalCheckResult TraversalCheckResult, FVector FrontLedgeLocationCollisionCheck) const
{
	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), Character->GetActorLocation(), FrontLedgeLocationCollisionCheck, FColor::Red, false, 2.f);
	}

	FHitResult HitResult;
	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, Character->GetActorLocation(), FrontLedgeLocationCollisionCheck, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), FCollisionQueryParams(FName(TEXT("")), false, Character));

	return HitResult;
}

FHitResult UTraversalComponent::CheckTraceForBackLedge(FTraversalCheckResult TraversalCheckResult, FVector FrontLedgeLocationCollisionCheck, FVector BackLedgeLocationCollisionCheck) const
{
	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), FrontLedgeLocationCollisionCheck, BackLedgeLocationCollisionCheck, FColor::Blue, false, 2.f);
	}

	FHitResult HitResult;
	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, FrontLedgeLocationCollisionCheck, BackLedgeLocationCollisionCheck, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), FCollisionQueryParams(FName(TEXT("")), false, Character));

	return HitResult;
}

FHitResult UTraversalComponent::CheckTraceForBackFloor(FTraversalCheckResult TraversalCheckResult, FVector BackLedgeLocationCollisionCheck) const
{
	// Add a -Z buffer for the trace
	const FVector ForwardVector = (TraversalCheckResult.BackLedgeLocation - TraversalCheckResult.FrontLedgeLocation).GetSafeNormal();
	const FVector TraceEndLocation = TraversalCheckResult.BackLedgeNormal * (CapsuleRadius + 2.f) + TraversalCheckResult.BackLedgeLocation + FVector(0.f, 0.f, -1000.f);

	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), BackLedgeLocationCollisionCheck, TraceEndLocation, FColor::Blue, false, 2.f);
	}

	FHitResult HitResult;
	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, BackLedgeLocationCollisionCheck, TraceEndLocation, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), FCollisionQueryParams(FName(TEXT("")), false, Character));

	if (DrawDebug)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 12, FColor::Yellow, false, 2.f);
	}

	return HitResult;
}

