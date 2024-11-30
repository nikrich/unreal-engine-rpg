// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <UI/Widget/AuraUserWidget.h>
#include <UI/WidgetController/OverlayWidgetController.h>
#include "AuraHUD.generated.h"


class UOverlayWidgetController;
class UAuraUserWidget;
class APlayerController;
struct FWidgetControllerParams;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);

	void InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;


	
};
