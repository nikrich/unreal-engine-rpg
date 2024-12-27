// Copyright Hungry Ghost


#include "Traversal/TraversableBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ATraversableBlock::ATraversableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called when the game starts or when spawned
void ATraversableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATraversableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

