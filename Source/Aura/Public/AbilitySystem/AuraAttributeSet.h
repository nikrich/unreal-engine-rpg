// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	// Context

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	FGameplayEffectContextHandle EffectContextHandle;

	// Source

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<AActor> SourceAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<AController> SourceController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<ACharacter> SourceCharacter = nullptr;

	// Target

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<AActor> TargetAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<AController> TargetController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
	TObjectPtr<ACharacter> TargetCharacter = nullptr;

};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * Primary Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

	/*
	 * Vital Attributes 
	 */
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	// Mana and Max Mana
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Effect Properties")
	FEffectProperties EffectProperties;

	/*
	 * Primary Attributes Function
	 */

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor);


	/*
	 * Vital Attributes Function
	 */

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

};
