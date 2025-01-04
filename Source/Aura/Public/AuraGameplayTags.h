// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura	Gameplay Tags
 * 
 * Singleton class that holds all the gameplay tags for the game.
 */


struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// Primary Attributes

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	// Secondary Attributes

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	// Resistances

	FGameplayTag Attributes_Resistances_Fire;
	FGameplayTag Attributes_Resistances_Ballistic;
	FGameplayTag Attributes_Resistances_Energy;
	FGameplayTag Attributes_Resistances_Kinetic;
	FGameplayTag Attributes_Resistances_Piercing;
	FGameplayTag Attributes_Resistances_Toxic;
	FGameplayTag Attributes_Resistances_Radiation;
	FGameplayTag Attributes_Resistances_Shock;
	FGameplayTag Attributes_Resistances_Digital;
	FGameplayTag Attributes_Resistances_Viral;
	FGameplayTag Attributes_Resistances_Sonic;
	FGameplayTag Attributes_Resistances_Psychological;
	FGameplayTag Attributes_Resistances_Nanite;
	FGameplayTag Attributes_Resistances_Acid;
	FGameplayTag Attributes_Resistances_Biological;


	// Input Tags

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	// Damage

	FGameplayTag Damage;
	FGameplayTag Damage_Fire; // Damage from fire, explosions, or overheating.
	FGameplayTag Damage_Ballistic; // Damage from bullets, arrows, or other projectiles.
	FGameplayTag Damage_Energy; // Damage from lasers, plasma, or other energy weapons.
	FGameplayTag Damage_Kinetic; // Damage from physical impacts.
	FGameplayTag Damage_Piercing; // Damage from sharp objects.
	FGameplayTag Damage_Toxic; // Damage from chemical, biological, or nanotechnological toxins.
	FGameplayTag Damage_Radiation; // Damage from exposure to radioactive zones or corrupted energy sources.
	FGameplayTag Damage_Shock; // Damage from tasers, EMPs, or malfunctioning cybernetics.
	FGameplayTag Damage_Digital; // Damage to the nervous system or cybernetic implants via hacking, EMPs, or neural overloads.
	FGameplayTag Damage_Viral; // Damage caused by malware, AI corruption, or data-based attacks on cybernetic systems.
	FGameplayTag Damage_Sonic; // Damage from sound-based weapons or environmental hazards like collapsing buildings.
	FGameplayTag Damage_Psychological; // Mental damage caused by fear, trauma, or exposure to terrifying corporate propaganda.
	FGameplayTag Damage_Nanite; // Damage caused by rogue nanobots consuming organic or synthetic materials.
	FGameplayTag Damage_Acid; // Damage from acidic substances that corrode armor, cybernetics, or flesh.
	FGameplayTag Damage_Biological; // Damage from biological weapons, infections, or mutated wildlife.

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag Effects_HitReact;


private:
	static FAuraGameplayTags GameplayTags;
};
