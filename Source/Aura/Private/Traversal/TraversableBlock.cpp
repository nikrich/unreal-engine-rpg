// Copyright Hungry Ghost


#include "Traversal/TraversableBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Traversal/TraversalComponent.h"

// Sets default values
ATraversableBlock::ATraversableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Static Mesh
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BlockMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Create 4 Splines
	Ledge1 = CreateDefaultSubobject<USplineComponent>(TEXT("Ledge1"));
	Ledge2 = CreateDefaultSubobject<USplineComponent>(TEXT("Ledge2"));
	Ledge3 = CreateDefaultSubobject<USplineComponent>(TEXT("Ledge3"));
	Ledge4 = CreateDefaultSubobject<USplineComponent>(TEXT("Ledge4"));

	Ledge1->AttachToComponent(BlockMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Ledge2->AttachToComponent(BlockMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Ledge3->AttachToComponent(BlockMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Ledge4->AttachToComponent(BlockMesh, FAttachmentTransformRules::KeepRelativeTransform);

	Ledges.Add(Ledge1);
	Ledges.Add(Ledge2);
	Ledges.Add(Ledge3);
	Ledges.Add(Ledge4);

	OppositeLedges.Add(Ledge1, Ledge2);
	OppositeLedges.Add(Ledge2, Ledge1);
	OppositeLedges.Add(Ledge3, Ledge4);
	OppositeLedges.Add(Ledge4, Ledge3);

}

// Called when the game starts or when spawned
void ATraversableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATraversableBlock::GetLedgeTransforms(FVector HitLocation, FVector ActorLocation, FTraversalCheckResult& CheckResult)
{
	USplineComponent* ClosestLedge = FindClosestLedge(ActorLocation);

	if (!ClosestLedge)
	{
		CheckResult.bHasFrontLedge = false;
		return;
	}

	// Make sure the ledge is wide enough. If not, the front ledge will not be valid.

	const float LedgeLength = ClosestLedge->GetSplineLength();

	if (LedgeLength < MinLedgeLength)
	{
		CheckResult.bHasFrontLedge = false;
		return;
	}

	// Get the closest point on the ledge to the actor, and clamp the location so that it can't be too close to the end of the ledge. 
	// This prevents the character from floating if they traverse near a corner. The clamped location will always be half the "min ledge width" from the edge. 
	// If the min ledge width is 60 units, the ledge location will always be at least 30 units away from a corner.

	const FVector Location = ClosestLedge->FindLocationClosestToWorldLocation(HitLocation, ESplineCoordinateSpace::Local);
	const float DistanceAlongSpline = ClosestLedge->GetDistanceAlongSplineAtLocation(Location, ESplineCoordinateSpace::Local);

	const float HalfLedgeLength = LedgeLength / 2.f;
	const float AcceptableGrabDistanceOnSpline = FMath::Clamp(DistanceAlongSpline, HalfLedgeLength, LedgeLength - HalfLedgeLength);

	const FTransform GrabTransform = ClosestLedge->GetTransformAtDistanceAlongSpline(AcceptableGrabDistanceOnSpline, ESplineCoordinateSpace::Local);
	const FVector GrabLocation = GrabTransform.GetLocation();
	const FVector GrabUpVector = GrabTransform.GetRotation().GetUpVector();

	// Draw Debug Sphere
	if (DrawDebug)
	{
		DrawDebugSphere(GetWorld(), GrabLocation, 10.f, 12, FColor::Green, false, 2.f);
	}

	// Add Data to Check Result
	CheckResult.bHasFrontLedge = true;
	CheckResult.FrontLedgeLocation = GrabLocation;
	CheckResult.FrontLedgeNormal = GrabUpVector;

	// Find the Opposite Ledge
	USplineComponent* OppositeLedge = OppositeLedges[ClosestLedge];

	if (!OppositeLedge) 
	{
		CheckResult.bHasBackLedge = false;
		return;
	}

	const FTransform OppositeLedgeTransform = OppositeLedge->FindTransformClosestToWorldLocation(GrabLocation, ESplineCoordinateSpace::World);
	const FVector OppositeLedgeLocation = OppositeLedgeTransform.GetLocation();
	const FVector OppositeLedgeUpVector = OppositeLedgeTransform.GetRotation().GetUpVector();

	// Draw Debug Sphere
	if (DrawDebug)
	{
		DrawDebugSphere(GetWorld(), OppositeLedgeLocation, 10.f, 12, FColor::Blue, false, 2.f);
	}

	// Add Data to Check Result
	CheckResult.bHasBackLedge = true;
	CheckResult.BackLedgeLocation = OppositeLedgeLocation;
	CheckResult.BackLedgeNormal = OppositeLedgeUpVector;
}

/* 
 * Iterate through all the closest points on all available ledges to find the closest one.An offset is added away
 * from the ledge using its normal to prevent corners from having the same location. 
 * If not, traversing against a corner  would be inconsistent.
 */

USplineComponent* ATraversableBlock::FindClosestLedge(FVector ActorLocation)
{
	
	float ClosestDistance = FLT_MAX;
	USplineComponent* ClosestLedge = nullptr;

	for (USplineComponent* Ledge : Ledges)
	{
		const FVector Location = Ledge->FindLocationClosestToWorldLocation(ActorLocation, ESplineCoordinateSpace::World);

		// Add an offset for the corners (I think)
		const FVector UpVector = Ledge->FindUpVectorClosestToWorldLocation(ActorLocation, ESplineCoordinateSpace::World) * 10.f;

		const FVector CombinedLocation = Location + UpVector;

		float Distance = FVector::Dist(ActorLocation, CombinedLocation);

		if (Distance < ClosestDistance) {
			ClosestDistance = Distance;
			ClosestLedge = Ledge;
		}
	}

	return ClosestLedge;
}

