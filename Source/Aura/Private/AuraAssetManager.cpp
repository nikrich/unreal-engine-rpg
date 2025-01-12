// Copyright Hungry Ghost


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"
#include <AbilitySystem/ExecCalc/ExecCalc_Damage.h>

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitializeNativeGameplayTags();

	// Init Exec Calc Damage Capture Defs
	UExecCalc_Damage::InitializeStaticTagsToCaptureDefsMap();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
