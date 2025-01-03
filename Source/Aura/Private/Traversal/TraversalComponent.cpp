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

FTraversalInputType UTraversalComponent::GetTraversalInput() const
{
	// Gets how fast the character is moving in its forward direction and uses the value to scale the distance of the forward trace.
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	EMovementMode MovementMode = MovementComponent->MovementMode;
	FVector Velocity = MovementComponent->Velocity;
	FVector UnrotatedVelocity = Character->GetActorRotation().UnrotateVector(Velocity);
	float UnrotatedMapClampedVelocity = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 500.0f), FVector2D(75.f, 350.f), UnrotatedVelocity.X);
	FVector ForwardVector = Character->GetActorForwardVector();

	// Don't traverse if the character is falling or flying.
	if (MovementMode == EMovementMode::MOVE_Falling || MovementMode == EMovementMode::MOVE_Flying) 
	{
		return FTraversalInputType(ForwardVector, 0.0f, FVector(), FVector(), 0.0f, 0.0f);
	}

	// These trace values are hardcoded for now, but will be replaced with variables that can be set in the editor.
	return FTraversalInputType(ForwardVector, UnrotatedMapClampedVelocity, FVector(0.f, 0.f, 50.f), FVector(0.f, 0.f, 50.f), 30.0f, 60.f);
}

void UTraversalComponent::PerformTraversalTrace()
{
	TraversalCheckResult = FTraversalCheckResult();
	
	FTraversableBlockResult TraversableBlock = CheckIfObjectIsTraversable();

	if (!TraversableBlock.TraversableBlock)
	{
		return;
	}

	TraversalCheckResult.HitComponent = TraversableBlock.HitComponent;

	TraversableBlock.TraversableBlock->SetLedgeTransforms(TraversableBlock.ImpactPoint, Character->GetActorLocation(), TraversalCheckResult);

	if (!TraversalCheckResult.bHasFrontLedge) {
		return;
	}


	// Perform a trace from the actors location up to the front ledge location to determine
	// if there is room for the actor to move up to it. If so, continue the function. If not, exit early.
	
	SetFrontLedgeInfo(TraversalCheckResult);

	// Perform a trace across the top of the obstacle from the front ledge to the back ledge to see if theres room for the actor to move across it.
	// If there is room, continue the function. If not, exit early.

	SetBackLedgeInfo(TraversalCheckResult);
	
	// Trace downward from the back ledge location (using the height of the obstacle for the distance) to find the floor. 
	// If there is a floor, save its location and the back ledges height (using the distance between the back ledge and the floor). 
	// If no floor was found, invalidate the back floor.
	 
	SetBackFloorInfo(TraversalCheckResult);
	
	// Once all of the Meta Data has been collected, the Montage Chooser will be called to determine the best animation to play.

	FTraversalChooserInputs MontageChooserInputs = MakeChooserInputs();
	OnTraversalCheckComplete.Broadcast(MontageChooserInputs);
}

FTraversableBlockResult UTraversalComponent::CheckIfObjectIsTraversable() const
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
		return FTraversableBlockResult();
	}

	// Hit Has Occurred

	AActor* HitActor = HitResult.GetActor();
	ATraversableBlock* TraversableBlock = Cast<ATraversableBlock>(HitActor);

	if (!TraversableBlock)
	{
		return FTraversableBlockResult();
	}

	return FTraversableBlockResult(TraversableBlock, HitResult.Component.Get(), HitResult.ImpactPoint);
}


void UTraversalComponent::SetFrontLedgeInfo(FTraversalCheckResult& CheckResult)
{
	FrontLedgeLocationCollisionCheck = TraversalCheckResult.FrontLedgeLocation + (TraversalCheckResult.FrontLedgeNormal * CapsuleRadius + 2) + FVector(0.f, 0.f, CapsuleHalfHeight + 2.f);

	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), Character->GetActorLocation(), FrontLedgeLocationCollisionCheck, FColor::Red, false, 2.f);
		DrawDebugSphere(GetWorld(), FrontLedgeLocationCollisionCheck, 10.f, 12, FColor::Red, false, 2.f);
	}

	FHitResult HitResult;

	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("")), false);
	Params.AddIgnoredActor(TraversalCheckResult.HitComponent->GetOwner());
	Params.AddIgnoredActor(Character);

	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, Character->GetActorLocation(), FrontLedgeLocationCollisionCheck, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), Params);

	if (DrawDebug && GEngine && bTraceSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Front Edge Traversal Check: %s"), *HitResult.GetActor()->GetName()));
	
	}

	const bool bCannotTraverseLedge = HitResult.bBlockingHit;

	// If the front ledge is blocked for traversal by another object, exit early.
	if (bCannotTraverseLedge)
	{
		return;
	}

	// Save the height of the obstacle using the delta between the actor and front ledge transform.
	TraversalCheckResult.ObstacleHeight = FMath::Abs(TraversalCheckResult.FrontLedgeLocation.Z - (Character->GetActorLocation().Z - CapsuleHalfHeight));
}

void UTraversalComponent::SetBackLedgeInfo(FTraversalCheckResult& CheckResult)
{
	BackLedgeLocationCollisionCheck = TraversalCheckResult.BackLedgeLocation + (TraversalCheckResult.BackLedgeNormal * CapsuleRadius + 2) + FVector(0.f, 0.f, CapsuleHalfHeight + 2.f);

	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), FrontLedgeLocationCollisionCheck, BackLedgeLocationCollisionCheck, FColor::Blue, false, 2.f);
	}

	FHitResult HitResult;

	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("")), false);
	Params.AddIgnoredActor(TraversalCheckResult.HitComponent->GetOwner());
	Params.AddIgnoredActor(Character);

	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, FrontLedgeLocationCollisionCheck, BackLedgeLocationCollisionCheck, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), Params);

	const bool bIsBlockedFromRunningToBackLedge = HitResult.bBlockingHit;

	if (bIsBlockedFromRunningToBackLedge)
	{
		TraversalCheckResult.bHasBackLedge = false;
	}
	else
	{
		TraversalCheckResult.ObstacleDepth = FMath::Abs(FVector::Dist(TraversalCheckResult.FrontLedgeLocation, TraversalCheckResult.BackLedgeLocation));
	}
}

void UTraversalComponent::SetBackFloorInfo(FTraversalCheckResult& CheckResult)
{
	// Add a -Z buffer for the trace
	const FVector BackledgeOffset = TraversalCheckResult.BackLedgeNormal * (CapsuleRadius + 2.f);
	const FVector TraceEndLocation = BackledgeOffset + TraversalCheckResult.BackLedgeLocation + FVector(0.f, 0.f, -1000.f);

	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), BackLedgeLocationCollisionCheck, TraceEndLocation, FColor::Blue, false, 2.f);
	}

	FHitResult HitResult;

	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("")), false);
	Params.AddIgnoredActor(TraversalCheckResult.HitComponent->GetOwner());
	Params.AddIgnoredActor(Character);

	bool bTraceSuccess = GetWorld()->SweepSingleByChannel(HitResult, BackLedgeLocationCollisionCheck, TraceEndLocation, FQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), Params);

	if (DrawDebug)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 12, FColor::Yellow, false, 2.f);
	}

	const bool bHasBackFloor = HitResult.bBlockingHit;

	if (bHasBackFloor)
	{
		TraversalCheckResult.bHasBackFloor = true;
		TraversalCheckResult.BackFloorLocation = HitResult.ImpactPoint;
		TraversalCheckResult.BackLedgeHeight = TraversalCheckResult.BackLedgeLocation.Z - TraversalCheckResult.BackFloorLocation.Z;
	}
	else
	{
		TraversalCheckResult.bHasBackFloor = false;
	}
}

/*
 * Used by The Chooser Table to Identify Valid Animations
 */

FTraversalChooserInputs UTraversalComponent::MakeChooserInputs() const
{
	FTraversalChooserInputs ChooserInputs = FTraversalChooserInputs();
	ChooserInputs.bHasBackFloor = TraversalCheckResult.bHasBackFloor;
	ChooserInputs.bHasBackLedge = TraversalCheckResult.bHasBackLedge;
	ChooserInputs.bHasFrontLedge = TraversalCheckResult.bHasFrontLedge;
	ChooserInputs.ObstacleDepth = TraversalCheckResult.ObstacleDepth;
	ChooserInputs.ObstacleHeight = TraversalCheckResult.ObstacleHeight;
	ChooserInputs.BackLedgeHeight = TraversalCheckResult.BackLedgeHeight;
	ChooserInputs.ActionType = TraversalCheckResult.ActionType;
	ChooserInputs.MovementMode = Character->GetCharacterMovement()->MovementMode;
	ChooserInputs.Gait = Gait;
	ChooserInputs.Speed = Character->GetCharacterMovement()->Velocity.Length();

	return ChooserInputs;
}

