// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include <Character/AuraCharacterBase.h>
#include "TraversalComponent.h"
#include "TraversalComponentV2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraversalV2CheckComplete, FTraversalChooserInputs, ChooserInputs);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AURA_API UTraversalComponentV2 : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTraversalComponentV2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Traversal Info")
	EGait Gait;

public:
	ACharacter* Character;

	UFUNCTION(BlueprintCallable, Category = "Traversal Info")
	void PerformTraversalTrace();

	UPROPERTY(BlueprintAssignable, Category = "Traversal Info")
	FOnTraversalV2CheckComplete OnTraversalCheckComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traversal Info")
	FTraversalCheckResult TraversalCheckResult;

private:

	UPROPERTY(EditAnywhere, Category = "Capsule")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, Category = "Capsule")
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, Category = "Capsule")
	FVector FrontLedgeLocationCollisionCheck;

	UPROPERTY(EditAnywhere, Category = "Capsule")
	FVector BackLedgeLocationCollisionCheck;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawDebug;

	FTraversalInputType GetTraversalInput() const;
	FTraversableBlockResult CheckIfObjectIsTraversable() const;
	void SetFrontLedgeInfo(FTraversalCheckResult& CheckResult);
	void SetBackLedgeInfo(FTraversalCheckResult& CheckResult);
	void SetBackFloorInfo(FTraversalCheckResult& CheckResult);
	FTraversalChooserInputs MakeChooserInputs() const;
};
