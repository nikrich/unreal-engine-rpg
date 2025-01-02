// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "TraversalComponent.generated.h"

UENUM(BlueprintType)
enum class ETraversalActionType : uint8
{
	None,
	Hurdle,
	Vault,
	Mantle
};

USTRUCT(BlueprintType)
struct FTraversalInputType
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector TraceForwardVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float TraceForwardDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector TraceOriginOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector TraceEndOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float TraceHalfHeight;
};

USTRUCT(BlueprintType)
struct FTraversalCheckResult
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	ETraversalActionType ActionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	bool bHasFrontLedge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector FrontLedgeLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector FrontLedgeNormal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	bool bHasBackLedge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector BackLedgeLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector BackLedgeNormal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	bool bHasBackFloor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	FVector BackFloorLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float ObstacleHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float ObstacleDepth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float BackLedgeHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	UPrimitiveComponent* HitComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	UAnimMontage* ChosenMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float StartTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	float EndTime;

};

USTRUCT(BlueprintType)
struct FTraceResult
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	bool TraceCheckFailed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal Info")
	bool MontageSelectionFailed;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UTraversalComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraversalComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	ACharacter* Character;

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	void TryTraversalAction();

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	FTraversalInputType GetTraversalInput() const;

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	FTraceResult PerformTrace() const;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, Category = "Input")
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, Category = "Input")
	bool DrawDebug;
};
