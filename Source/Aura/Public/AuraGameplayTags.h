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

	FGameplayTag Attributes_Primary_Body; // Physical strength, endurance, and toughness. Affects melee damage, health, and resistance to physical damage.
	FGameplayTag Attributes_Primary_Agility; // Dexterity, speed, and reflexes. Affects movement speed, evasion, and ranged weapon accuracy.
	FGameplayTag Attributes_Primary_Intellect; // Cognitive and problem-solving ability. Affects hacking, crafting, and data analysis.
	FGameplayTag Attributes_Primary_Charisma; // Social skills and persuasion. Affects dialogue options, influence, and reputation.
	FGameplayTag Attributes_Primary_CyberAffinity; // Ability to handle cybernetic implants and tech upgrades. Affects cybernetic implants, hacking defense, and digital resistance.
	FGameplayTag Attributes_Primary_Perception; // Awareness of surroundings and attention to detail. Affects critical hit chance, stealth detection, and spotting traps.
	FGameplayTag Attributes_Primary_Willpower; // Mental resilience and focus. Affects resistance to psychological and digital attacks.
	FGameplayTag Attributes_Primary_Luck; // Random chance and serendipity. Affects critical hits, loot quality, and random encounters.


	// Secondary Attributes
	
	FGameplayTag Attributes_Stamina; // The energy pool used for actions like sprinting, melee. Affects endurance during combat and exploration.
	FGameplayTag Attributes_ArmorRating; // Resistance to physical damage. Reduces damage taken from physical attacks.
	FGameplayTag Attributes_ArmorPenetration; // The ability to bypass enemy armor. Increases damage dealt to armored targets.
	FGameplayTag Attributes_Evasion; // The chance to dodge incoming attacks. Affects survivability in combat.
	FGameplayTag Attributes_Accuracy; // The ability to hit a target with ranged weapons. Affects hit chance for ranged attacks.
	FGameplayTag Attributes_CriticalChance; // The chance to deal extra damage on attacks. Increases likelihood of critical hits.
	FGameplayTag Attributes_CriticalDamage; // The amount of extra damage dealt on critical hits.
	FGameplayTag Attributes_HackingPower; // The ability to break through digital defenses. Affects success rate in hacking mini-games.
	FGameplayTag Attributes_Persuasion; // The ability to influence NPCs in dialogue. Unlocks dialogue options and reduces hostility.
	FGameplayTag Attributes_Stealth; // The ability to avoid detection. Affects sneaking and hiding from enemies.
	FGameplayTag Attributes_MaxHealth; // The amount of damage a character can take before dying. Determines maximum health pool.
	FGameplayTag Attributes_MaxEnergy; // The amount of energy a character can spend on abilities. Determines maximum mana pool.

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
	FGameplayTag Attributes_CriticalHitResistance;


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
