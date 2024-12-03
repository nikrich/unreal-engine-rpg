// Copyright Hungry Ghost


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include <AbilitySystem/Data/AttributeInfo.h>
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FGameplayTag StrengthTag = FAuraGameplayTags::Get().Attributes_Primary_Strength;
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(StrengthTag);
	Info.AttributeValue = AuraAttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
