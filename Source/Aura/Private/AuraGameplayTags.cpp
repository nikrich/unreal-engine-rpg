// Copyright Hungry Ghost


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{

	// Primary Attributes

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases Physical Damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases Magical Damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Reduces Damage Taken"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases Health and Health Regeneration"));

	// Secondary Attributes

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces Damage Taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores a portion of the target's Armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to block incoming attacks"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to deal double damage"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Increases damage dealt on critical hits"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces damage taken from critical hits"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Restores Health over time"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Restores Mana over time"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Increases maximum Health"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Increases maximum Mana"));

	// Resistances

	GameplayTags.Attributes_Resistances_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Fire"), FString("Reduces Fire Damage Taken"));
	GameplayTags.Attributes_Resistances_Ballistic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Ballistic"), FString("Reduces Ballistic Damage Taken"));
	GameplayTags.Attributes_Resistances_Energy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Energy"), FString("Reduces Energy Damage Taken"));
	GameplayTags.Attributes_Resistances_Kinetic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Kinetic"), FString("Reduces Kinetic Damage Taken"));
	GameplayTags.Attributes_Resistances_Piercing = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Piercing"), FString("Reduces Piercing Damage Taken"));
	GameplayTags.Attributes_Resistances_Toxic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Toxic"), FString("Reduces Toxic Damage Taken"));
	GameplayTags.Attributes_Resistances_Radiation = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Radiation"), FString("Reduces Radiation Damage Taken"));
	GameplayTags.Attributes_Resistances_Shock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Shock"), FString("Reduces Shock Damage Taken"));
	GameplayTags.Attributes_Resistances_Digital = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Digital"), FString("Reduces Digital Damage Taken"));
	GameplayTags.Attributes_Resistances_Viral = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Viral"), FString("Reduces Viral Damage Taken"));
	GameplayTags.Attributes_Resistances_Sonic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Sonic"), FString("Reduces Sonic Damage Taken"));
	GameplayTags.Attributes_Resistances_Psychological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Psychological"), FString("Reduces Psychological Damage Taken"));
	GameplayTags.Attributes_Resistances_Nanite = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Nanite"), FString("Reduces Nanite Damage Taken"));
	GameplayTags.Attributes_Resistances_Acid = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Acid"), FString("Reduces Acid Damage Taken"));
	GameplayTags.Attributes_Resistances_Biological = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Biological"), FString("Reduces Biological Damage Taken"));

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
