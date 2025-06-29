// Copyright Hungry Ghost

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadDataLayerTriggerVolume.generated.h"

class UBoxComponent;

UCLASS()
class AURA_API ALoadDataLayerTriggerVolume : public AActor
{
    GENERATED_BODY()

public:
    ALoadDataLayerTriggerVolume();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Layer")
    TObjectPtr<UDataLayerAsset> DataLayerAssetToActivate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Layer")
    TObjectPtr<UDataLayerAsset> DataLayerAssetToDeactivate;

private:
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerVolume;

    void LoadDataLayer();
};