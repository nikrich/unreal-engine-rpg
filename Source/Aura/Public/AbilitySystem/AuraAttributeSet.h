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

	UPROPERTY(ReplicatedUsing = OnRep_Energy, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Energy)

	/*
	 * Meta Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage)

	/*
	 * Primary Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Body, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Body;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Body)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Agility, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Agility;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Agility)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Intellect, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Intellect;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Intellect)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Charisma, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Charisma;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Charisma)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_CyberAffinity, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_CyberAffinity;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_CyberAffinity)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Perception, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Perception;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Perception)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Willpower, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Willpower;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Willpower)

	UPROPERTY(ReplicatedUsing = OnRep_Primary_Luck, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Primary_Luck;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Primary_Luck)

	/*
	 * Secondary Attributes
	 */


	UPROPERTY(ReplicatedUsing = OnRep_Secondary_Stamina, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_Stamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_Stamina)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_ArmorRating, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_ArmorRating;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_ArmorRating)
	
	UPROPERTY(ReplicatedUsing = OnRep_Secondary_ArmorPenetration, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_ArmorPenetration)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_Evasion, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_Evasion;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_Evasion)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_Accuracy, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_Accuracy;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_Accuracy)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_CriticalChance, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_CriticalChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_CriticalChance)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_CriticalDamage, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_CriticalDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_CriticalDamage)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_HackingPower, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_HackingPower;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_HackingPower)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_Persuasion, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_Persuasion;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_Persuasion)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_Stealth, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_Stealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_Stealth)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_MaxHealth, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_MaxHealth)

	UPROPERTY(ReplicatedUsing = OnRep_Secondary_MaxEnergy, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Secondary_MaxEnergy;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Secondary_MaxEnergy)


	UPROPERTY(BlueprintReadOnly, Category = "Effect Properties")
	FEffectProperties EffectProperties;

	/*
	 * Resistance Attributes
	 */

	UPROPERTY(ReplicatedUsing = OnRep_FireResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Fire;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Fire)

	UPROPERTY(ReplicatedUsing = OnRep_BallisticResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Ballistic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Ballistic)

	UPROPERTY(ReplicatedUsing = OnRep_EnergyResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Energy;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Energy)

	UPROPERTY(ReplicatedUsing = OnRep_KineticResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Kinetic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Kinetic)

	UPROPERTY(ReplicatedUsing = OnRep_PiercingResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Piercing;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Piercing)

	UPROPERTY(ReplicatedUsing = OnRep_ToxicResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Toxic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Toxic)

	UPROPERTY(ReplicatedUsing = OnRep_RadiationResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Radiation;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Radiation)

	UPROPERTY(ReplicatedUsing = OnRep_ShockResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Shock;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Shock)

	UPROPERTY(ReplicatedUsing = OnRep_DigitalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Digital;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Digital)

	UPROPERTY(ReplicatedUsing = OnRep_ViralResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Viral;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Viral)

	UPROPERTY(ReplicatedUsing = OnRep_SonicResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Sonic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Sonic)

	UPROPERTY(ReplicatedUsing = OnRep_PsychologicalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Psychological;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Psychological)

	UPROPERTY(ReplicatedUsing = OnRep_NaniteResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Nanite;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Nanite)

	UPROPERTY(ReplicatedUsing = OnRep_AcidResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Acid;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Acid)

	UPROPERTY(ReplicatedUsing = OnRep_BiologicalResistance, BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData Resistance_Biological;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_Biological)

	UPROPERTY(ReplicatedUsing = OnRep_Resistance_CriticalHit, BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Resistance_CriticalHit;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance_CriticalHit)

	/*
	 * Vital Attributes Function
	 */

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldEnergy);

	/*
	 * Primary Attributes Function
	 */

	UFUNCTION()
	void OnRep_Primary_Body(const FGameplayAttributeData& OldPrimary_Body);

	UFUNCTION()
	void OnRep_Primary_Agility(const FGameplayAttributeData& OldPrimary_Agility);

	UFUNCTION()
	void OnRep_Primary_Intellect(const FGameplayAttributeData& OldPrimary_Intellect);

	UFUNCTION()
	void OnRep_Primary_Charisma(const FGameplayAttributeData& OldPrimary_Charisma);

	UFUNCTION()
	void OnRep_Primary_CyberAffinity(const FGameplayAttributeData& OldPrimary_CyberAffinity);

	UFUNCTION()
	void OnRep_Primary_Perception(const FGameplayAttributeData& OldPrimary_Perception);

	UFUNCTION()
	void OnRep_Primary_Willpower(const FGameplayAttributeData& OldPrimary_Willpower);

	UFUNCTION()
	void OnRep_Primary_Luck(const FGameplayAttributeData& OldPrimary_Luck);

	/*
	 * Secondary Attributes Function
	 */

	
	UFUNCTION()
	void OnRep_Secondary_Stamina(const FGameplayAttributeData& OldSecondary_Stamina);

	UFUNCTION()
	void OnRep_Secondary_ArmorRating(const FGameplayAttributeData& OldArmorRating);

	UFUNCTION()
	void OnRep_Secondary_ArmorPenetration(const FGameplayAttributeData& OldArmorPeneration);

	UFUNCTION()
	void OnRep_Secondary_Evasion(const FGameplayAttributeData& OldEvasion);

	UFUNCTION()
	void OnRep_Secondary_Accuracy(const FGameplayAttributeData& OldAccuracy);

	UFUNCTION()
	void OnRep_Secondary_CriticalChance(const FGameplayAttributeData& OldCriticalChance);

	UFUNCTION()
	void OnRep_Secondary_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage);

	UFUNCTION()
	void OnRep_Secondary_HackingPower(const FGameplayAttributeData& OldHackingPower);

	UFUNCTION()
	void OnRep_Secondary_Persuasion(const FGameplayAttributeData& OldPersuasion);

	UFUNCTION()
	void OnRep_Secondary_Stealth(const FGameplayAttributeData& OldStealth);

	UFUNCTION()
	void OnRep_Secondary_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_Secondary_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);

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

	UFUNCTION()
	void OnRep_Resistance_CriticalHit(const FGameplayAttributeData& OldCriticalHitResistance);


private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties Props, float Damage, bool isBlockingHit, bool bIsCriticalHit) const;

};
