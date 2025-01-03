// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include <Character/AuraCharacterBase.h>
#include "TraversalComponent.generated.h"

UENUM(BlueprintType)
enum class ETraversalActionType : uint8
{
	None,
	Hurdle,
	Vault,
	Mantle
};

UENUM(BlueprintType)
enum class EGait : uint8
{
	Walk,
	Run,
	Sprint
};

USTRUCT(BlueprintType)
struct FTraversalInputType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector TraceForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float TraceForwardDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector TraceOriginOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector TraceEndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float TraceRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float TraceHalfHeight;
};

USTRUCT(BlueprintType)
struct FTraversalCheckResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	ETraversalActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasFrontLedge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector FrontLedgeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector FrontLedgeNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasBackLedge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector BackLedgeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector BackLedgeNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasBackFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FVector BackFloorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float ObstacleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float ObstacleDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float BackLedgeHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	UPrimitiveComponent* HitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	UAnimMontage* ChosenMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float EndTime;

};

/*
 * Used by The Chooser Table to Identify Valid Animations
 */

USTRUCT(BlueprintType)
struct FTraversalChooserInputs
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	ETraversalActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasFrontLedge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasBackLedge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool bHasBackFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float ObstacleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float ObstacleDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float BackLedgeHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	TEnumAsByte<EMovementMode> MovementMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	EGait Gait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	float Speed;

};

USTRUCT(BlueprintType)
struct FTraversalChooserOutputs
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	ETraversalActionType ActionType;
};

USTRUCT(BlueprintType)
struct FTraceResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool TraceCheckFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	bool MontageSelectionFailed;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraversalCheckComplete, FTraversalChooserInputs, ChooserInputs);

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

	UPROPERTY(EditAnyWhere, BlueprintReadonly, Category = "Combat")
	EGait Gait;

public:	
	ACharacter* Character;

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	FTraceResult PerformTraversalTrace();

	UPROPERTY(BlueprintAssignable, Category = "Traversal Info")
	FOnTraversalCheckComplete OnTraversalCheckComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FTraversalCheckResult TraversalCheckResult;

private:

	UPROPERTY(EditAnywhere, Category = "Capsule")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, Category = "Capsule")
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawDebug;

	FTraversalInputType GetTraversalInput() const;
	FHitResult CheckTraceForFrontLedge(FVector FrontLedgeLocationCollisionCheck) const;
	FHitResult CheckTraceForBackLedge(FVector FrontLedgeLocationCollisionCheck, FVector BackLedgeLocationCollisionCheck) const;
	FHitResult CheckTraceForBackFloor(FVector BackLedgeLocationCollisionCheck) const;
	FTraversalChooserInputs MakeChooserInputs() const;
};
