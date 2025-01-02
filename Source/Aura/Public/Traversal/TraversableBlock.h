// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraversableBlock.generated.h"

class USplineComponent;

UCLASS()
class AURA_API ATraversableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraversableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	void GetLedgeTransforms(FVector HitLocation, FVector ActorLocation, struct FTraversalCheckResult& CheckResult);

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	USplineComponent* FindClosestLedge(FVector ActorLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	USplineComponent* Ledge1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	USplineComponent* Ledge2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	USplineComponent* Ledge3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	USplineComponent* Ledge4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	TArray<USplineComponent*> Ledges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	TMap<USplineComponent*, USplineComponent*> OppositeLedges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	float MinLedgeLength = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversable Block")
	bool DrawDebug = false;
};
