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

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);

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


// Creates a delegate instance for a static function pointer
// This is very useful for creating a delegate instance for a static function pointer
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr;

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

	// The static function pointer for the attributes
	// See comments above for the TStaticFuncPtr
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay Tags")
	TArray<FGameplayTag> PrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay Tags")
	TArray<FGameplayTag> SecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay Tags")
	TArray<FGameplayTag> ResistanceAttributes;

	/*
	 * Vital Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	/*
	 * Meta Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage)

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
	 * Secondary Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor)

	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration)

	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance)

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance)

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage)

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance)

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration)

	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration)

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Effect Properties")
	FEffectProperties EffectProperties;

	/*
	 * Resistance Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_FireResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResistance)

	UPROPERTY(ReplicatedUsing = OnRep_BallisticResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData BallisticResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BallisticResistance)

	UPROPERTY(ReplicatedUsing = OnRep_EnergyResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData EnergyResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, EnergyResistance)

	UPROPERTY(ReplicatedUsing = OnRep_KineticResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData KineticResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, KineticResistance)

	UPROPERTY(ReplicatedUsing = OnRep_PiercingResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData PiercingResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PiercingResistance)

	UPROPERTY(ReplicatedUsing = OnRep_ToxicResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData ToxicResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ToxicResistance)

	UPROPERTY(ReplicatedUsing = OnRep_RadiationResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData RadiationResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, RadiationResistance)

	UPROPERTY(ReplicatedUsing = OnRep_ShockResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData ShockResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ShockResistance)

	UPROPERTY(ReplicatedUsing = OnRep_DigitalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData DigitalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, DigitalResistance)

	UPROPERTY(ReplicatedUsing = OnRep_ViralResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData ViralResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ViralResistance)

	UPROPERTY(ReplicatedUsing = OnRep_SonicResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData SonicResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, SonicResistance)

	UPROPERTY(ReplicatedUsing = OnRep_PsychologicalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData PsychologicalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PsychologicalResistance)

	UPROPERTY(ReplicatedUsing = OnRep_NaniteResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData NaniteResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, NaniteResistance)

	UPROPERTY(ReplicatedUsing = OnRep_AcidResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData AcidResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, AcidResistance)

	UPROPERTY(ReplicatedUsing = OnRep_BiologicalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData BiologicalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BiologicalResistance)

	/*
	 * Vital Attributes Function
	 */

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);

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
	 * Secondary Attributes Function
	 */

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

	/*
	 * Resistance Attributes Function
	 */

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);

	UFUNCTION()
	void OnRep_BallisticResistance(const FGameplayAttributeData& OldBallisticResistance);

	UFUNCTION()
	void OnRep_EnergyResistance(const FGameplayAttributeData& OldEnergyResistance);

	UFUNCTION()
	void OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance);

	UFUNCTION()
	void OnRep_PiercingResistance(const FGameplayAttributeData& OldPiercingResistance);

	UFUNCTION()
	void OnRep_ToxicResistance(const FGameplayAttributeData& OldToxicResistance);

	UFUNCTION()
	void OnRep_RadiationResistance(const FGameplayAttributeData& OldRadiationResistance);

	UFUNCTION()
	void OnRep_ShockResistance(const FGameplayAttributeData& OldShockResistance);

	UFUNCTION()
	void OnRep_DigitalResistance(const FGameplayAttributeData& OldDigitalResistance);

	UFUNCTION()
	void OnRep_ViralResistance(const FGameplayAttributeData& OldViralResistance);

	UFUNCTION()
	void OnRep_SonicResistance(const FGameplayAttributeData& OldSonicResistance);

	UFUNCTION()
	void OnRep_PsychologicalResistance(const FGameplayAttributeData& OldPsychologicalResistance);

	UFUNCTION()
	void OnRep_NaniteResistance(const FGameplayAttributeData& OldNaniteResistance);

	UFUNCTION()
	void OnRep_AcidResistance(const FGameplayAttributeData& OldAcidResistance);

	UFUNCTION()
	void OnRep_BiologicalResistance(const FGameplayAttributeData& OldBiologicalResistance);


private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties Props, float Damage, bool isBlockingHit, bool bIsCriticalHit) const;

};
