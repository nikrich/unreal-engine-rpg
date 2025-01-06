// Copyright Hungry Ghost


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes

	GameplayTags.Attributes_Primary_Body = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Body"), FString("Physical strength, endurance, and toughness. Affects melee damage, health, and resistance to physical damage."));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("Dexterity, speed, and reflexes. Affects movement speed, evasion, and ranged weapon accuracy."));
	GameplayTags.Attributes_Primary_Intellect = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intellect"), FString("Cognitive and problem-solving ability. Affects hacking, crafting, and data analysis."));
	GameplayTags.Attributes_Primary_Charisma = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Charisma"), FString("Social skills and persuasion. Affects dialogue options, influence, and reputation."));
	GameplayTags.Attributes_Primary_CyberAffinity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.CyberAffinity"), FString("Ability to handle cybernetic implants and tech upgrades. Affects cybernetic implants, hacking defense, and digital resistance."));
	GameplayTags.Attributes_Primary_Perception = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Perception"), FString("Awareness of surroundings and attention to detail. Affects critical hit chance, stealth detection, and spotting traps."));
	GameplayTags.Attributes_Primary_Willpower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Willpower"), FString("Mental resilience and focus. Affects resistance to psychological and digital attacks."));
	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Luck"), FString("Random chance and serendipity. Affects critical hits, loot quality, and random encounters."));

	// Secondary Attributes
	
	GameplayTags.Attributes_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Stamina"), FString("The energy pool used for actions like sprinting, melee. Affects endurance during combat and exploration."));
	GameplayTags.Attributes_ArmorRating = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorRating"), FString("Resistance to physical damage. Reduces damage taken from physical attacks."));
	GameplayTags.Attributes_ArmorPeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPeneration"), FString("The ability to bypass enemy armor. Increases damage dealt to armored targets."));
	GameplayTags.Attributes_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Evasion"), FString("The chance to dodge incoming attacks. Affects survivability in combat."));
	GameplayTags.Attributes_Accuracy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Accuracy"), FString("The ability to hit a target with ranged weapons. Affects hit chance for ranged attacks."));
	GameplayTags.Attributes_CriticalChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalChance"), FString("The chance to deal extra damage on attacks. Increases likelihood of critical hits."));
	GameplayTags.Attributes_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalDamage"), FString("The amount of extra damage dealt on critical hits."));
	GameplayTags.Attributes_HackingPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HackingPower"), FString("The ability to break through digital defenses. Affects success rate in hacking mini-games."));
	GameplayTags.Attributes_Persuasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Persuasion"), FString("The ability to influence NPCs in dialogue. Unlocks dialogue options and reduces hostility."));
	GameplayTags.Attributes_Stealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Stealth"), FString("The ability to avoid detection. Affects sneaking and hiding from enemies."));
	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("The amount of damage a character can take before dying. Determines maximum health pool."));
	GameplayTags.Attributes_MaxEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxEnergy"), FString("The amount of energy a character can spend on abilities. Determines maximum mana pool."));

	// Resistances

	GameplayTags.Attributes_Resistances_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Reduces Fire Damage Taken"));
	GameplayTags.Attributes_Resistances_Ballistic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Ballistic"), FString("Reduces Ballistic Damage Taken"));
	GameplayTags.Attributes_Resistances_Energy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Energy"), FString("Reduces Energy Damage Taken"));
	GameplayTags.Attributes_Resistances_Kinetic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Kinetic"), FString("Reduces Kinetic Damage Taken"));
	GameplayTags.Attributes_Resistances_Piercing = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Piercing"), FString("Reduces Piercing Damage Taken"));
	GameplayTags.Attributes_Resistances_Toxic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Toxic"), FString("Reduces Toxic Damage Taken"));
	GameplayTags.Attributes_Resistances_Radiation = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Radiation"), FString("Reduces Radiation Damage Taken"));
	GameplayTags.Attributes_Resistances_Shock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Shock"), FString("Reduces Shock Damage Taken"));
	GameplayTags.Attributes_Resistances_Digital = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Digital"), FString("Reduces Digital Damage Taken"));
	GameplayTags.Attributes_Resistances_Viral = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Viral"), FString("Reduces Viral Damage Taken"));
	GameplayTags.Attributes_Resistances_Sonic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Sonic"), FString("Reduces Sonic Damage Taken"));
	GameplayTags.Attributes_Resistances_Psychological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Psychological"), FString("Reduces Psychological Damage Taken"));
	GameplayTags.Attributes_Resistances_Nanite = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Nanite"), FString("Reduces Nanite Damage Taken"));
	GameplayTags.Attributes_Resistances_Acid = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Acid"), FString("Reduces Acid Damage Taken"));
	GameplayTags.Attributes_Resistances_Biological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Biological"), FString("Reduces Biological Damage Taken"));
	GameplayTags.Attributes_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.CriticalHitResistance"), FString("The ability to resist critical hits. Reduces extra damage taken from critical hits."));

	// Input tags

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Key 1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Key 2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Key 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Key 4"));

	// Damage Tags

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Ballistic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Ballistic"), FString("Ballistic Damage Type"));
	GameplayTags.Damage_Energy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Energy"), FString("Energy Damage Type"));
	GameplayTags.Damage_Kinetic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Kinetic"), FString("Kinetic Damage Type"));
	GameplayTags.Damage_Piercing = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Piercing"), FString("Piercing Damage Type"));
	GameplayTags.Damage_Toxic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Toxic"), FString("Toxic Damage Type"));
	GameplayTags.Damage_Radiation = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Radiation"), FString("Radiation Damage Type"));
	GameplayTags.Damage_Shock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Shock"), FString("Shock Damage Type"));
	GameplayTags.Damage_Digital = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Digital"), FString("Digital Damage Type"));
	GameplayTags.Damage_Viral = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Viral"), FString("Viral Damage Type"));
	GameplayTags.Damage_Sonic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Sonic"), FString("Sonic Damage Type"));
	GameplayTags.Damage_Psychological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Psychological"), FString("Psychological Damage Type"));
	GameplayTags.Damage_Nanite = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Nanite"), FString("Nanite Damage Type"));
	GameplayTags.Damage_Acid = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Acid"), FString("Acid Damage Type"));
	GameplayTags.Damage_Biological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Biological"), FString("Biological Damage Type"));

	// Damage Types to Resistances

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistances_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Ballistic, GameplayTags.Attributes_Resistances_Ballistic);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Energy, GameplayTags.Attributes_Resistances_Energy);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Kinetic, GameplayTags.Attributes_Resistances_Kinetic);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Piercing, GameplayTags.Attributes_Resistances_Piercing);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Toxic, GameplayTags.Attributes_Resistances_Toxic);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Radiation, GameplayTags.Attributes_Resistances_Radiation);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Shock, GameplayTags.Attributes_Resistances_Shock);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Digital, GameplayTags.Attributes_Resistances_Digital);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Viral, GameplayTags.Attributes_Resistances_Viral);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Sonic, GameplayTags.Attributes_Resistances_Sonic);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Psychological, GameplayTags.Attributes_Resistances_Psychological);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Nanite, GameplayTags.Attributes_Resistances_Nanite);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Acid, GameplayTags.Attributes_Resistances_Acid);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Biological, GameplayTags.Attributes_Resistances_Biological);

	// Effects

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag Granted When Attacked"));
}
