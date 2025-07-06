// Copyright Hungry Ghost


#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AuraAIController.h"
#include <Character/AuraEnemy.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>
#include "Components/SplineComponent.h"

AAuraAIController::AAuraAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);

	// Initial Spline for Movement
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraAIController::Tick(float DeltaTime)
{
	if (!bAutoRunning) return;

	if (AAuraEnemy* ControlledPawn = Cast<AAuraEnemy>(GetPawn()))
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= GetAutoRunAcceptanceRadius())
		{
			bAutoRunning = false;
		}
	}
}

void AAuraAIController::CalculatePath(FVector Location)
{
	if (AAuraEnemy* ControlledPawn = Cast<AAuraEnemy>(GetPawn()))
	{
		
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), Location))
		{
			if (NavPath->PathPoints.Num() != 0)
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}

				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;

				auto MovementDistance = Spline->GetSplineLength();
				// Set Gait based on how far the player needs to travel
				ControlledPawn->SetGaitFromDistance(MovementDistance);

				if (bDebug) {
					// Draw Debug Spline
					for (int32 i = 0; i < NavPath->PathPoints.Num() - 1; ++i)
					{
						DrawDebugLine(
							GetWorld(),
							NavPath->PathPoints[i],
							NavPath->PathPoints[i + 1],
							FColor::Green,
							false,      // bPersistentLines
							5.0f,       // LifeTime
							0,          // DepthPriority
							5.0f        // Thickness
						);
					}
				}
			}
		}
	}
}

float AAuraAIController::GetAutoRunAcceptanceRadius() const
{
	if (AAuraEnemy* ControlledPawn = Cast<AAuraEnemy>(GetPawn()))
	{
		return ControlledPawn->GetCharacterClass() == ECharacterClass::Bruiser
			? MeleeAutoRunAcceptanceRadius
			: RangedAutoRunAcceptanceRadius;
	}

	return MeleeAutoRunAcceptanceRadius;
}
