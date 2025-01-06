// Copyright Hungry Ghost


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	UE_LOG(LogTemp, Log, TEXT("Looking for AttributeTag: %s"), *AttributeTag.ToString());

	for (const FAuraAttributeInfo& AttributeInfo : AttributeInformation)
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return AttributeInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeInfo not found for tag %s"), *AttributeTag.ToString());
	}

	return FAuraAttributeInfo();
}
