// Copyright Hungry Ghost


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include <AbilitySystem/Data/AttributeInfo.h>

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AuraAttributeSet](const FOnAttributeChangeData& Data)
			{
				FGameplayTag Tag = Pair.Key;
				FGameplayAttribute Attribute = Pair.Value();
				FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
				Info.AttributeValue = Attribute.GetNumericValueChecked(AuraAttributeSet);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}
}



void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		FGameplayTag Tag = Pair.Key;
		FGameplayAttribute Attribute = Pair.Value();
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
		Info.AttributeValue = Attribute.GetNumericValueChecked(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}

}