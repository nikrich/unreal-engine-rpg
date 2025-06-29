// Copyright Hungry Ghost


#include "LevelStreaming/LoadDataLayerTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "WorldPartition/DataLayer/DataLayerSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include <Character/AuraCharacter.h>
#include <Kismet/GameplayStatics.h>

ALoadDataLayerTriggerVolume::ALoadDataLayerTriggerVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALoadDataLayerTriggerVolume::OnOverlapBegin);
}

void ALoadDataLayerTriggerVolume::BeginPlay()
{
    Super::BeginPlay();
}

void ALoadDataLayerTriggerVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Only Allow the Main Character to Load Levels
    if (OtherActor && OtherActor->IsA<AAuraCharacter>())
    {
        // StartFade(1.0f);
        LoadDataLayer();
    }
}

void ALoadDataLayerTriggerVolume::LoadDataLayer()
{
    if (UDataLayerSubsystem* DataLayerSubsystem = GetWorld()->GetSubsystem<UDataLayerSubsystem>())
    {
        if (DataLayerAssetToActivate) {
            DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAssetToActivate, EDataLayerRuntimeState::Activated);
        }

        if (DataLayerAssetToDeactivate) {
            DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAssetToDeactivate, EDataLayerRuntimeState::Unloaded);
        }
    }
}

