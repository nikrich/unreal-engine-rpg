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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

};
