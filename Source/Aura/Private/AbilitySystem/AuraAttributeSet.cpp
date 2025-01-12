// Copyright Hungry Ghost


#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include <Net/UnrealNetwork.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "AuraGameplayTags.h"
#include <Interaction/CombatInterface.h>
#include <Kismet/GameplayStatics.h>
#include <Player/AuraPlayerController.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>

UAuraAttributeSet::UAuraAttributeSet()
{	
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	/**
	 * Primary Attributes
	 */

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Body, GetPrimary_BodyAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Agility, GetPrimary_AgilityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intellect, GetPrimary_IntellectAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Charisma, GetPrimary_CharismaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CyberAffinity, GetPrimary_CyberAffinityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Perception, GetPrimary_PerceptionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Willpower, GetPrimary_WillpowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Luck, GetPrimary_LuckAttribute);

	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Body);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Agility);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Intellect);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Charisma);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_CyberAffinity);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Perception);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Willpower);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Luck);

	/**
	 * Secondary Attributes
	 */

	TagsToAttributes.Add(GameplayTags.Attributes_Stamina, GetSecondary_StaminaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_ArmorRating, GetSecondary_ArmorRatingAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_ArmorPenetration, GetSecondary_ArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Evasion, GetSecondary_EvasionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Accuracy, GetSecondary_AccuracyAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_CriticalChance, GetSecondary_CriticalChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_CriticalDamage, GetSecondary_CriticalDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_HackingPower, GetSecondary_HackingPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Persuasion, GetSecondary_PersuasionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Stealth, GetSecondary_StealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxHealth, GetSecondary_MaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxEnergy, GetSecondary_MaxEnergyAttribute);

	SecondaryAttributes.Add(GameplayTags.Attributes_Stamina);
	SecondaryAttributes.Add(GameplayTags.Attributes_ArmorRating);
	SecondaryAttributes.Add(GameplayTags.Attributes_ArmorPenetration);
	SecondaryAttributes.Add(GameplayTags.Attributes_Evasion);
	SecondaryAttributes.Add(GameplayTags.Attributes_Accuracy);
	SecondaryAttributes.Add(GameplayTags.Attributes_CriticalChance);
	SecondaryAttributes.Add(GameplayTags.Attributes_CriticalDamage);
	SecondaryAttributes.Add(GameplayTags.Attributes_HackingPower);
	SecondaryAttributes.Add(GameplayTags.Attributes_Persuasion);
	SecondaryAttributes.Add(GameplayTags.Attributes_Stealth);
	SecondaryAttributes.Add(GameplayTags.Attributes_MaxHealth);
	SecondaryAttributes.Add(GameplayTags.Attributes_MaxEnergy);

	/**
	 * Resistances
	 */

	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Fire, GetResistance_FireAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Ballistic, GetResistance_BallisticAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Energy, GetResistance_EnergyAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Kinetic, GetResistance_KineticAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Piercing, GetResistance_PiercingAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Toxic, GetResistance_ToxicAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Radiation, GetResistance_RadiationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Shock, GetResistance_ShockAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Digital, GetResistance_DigitalAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Viral, GetResistance_ViralAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Sonic, GetResistance_SonicAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Psychological, GetResistance_PsychologicalAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Nanite, GetResistance_NaniteAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Acid, GetResistance_AcidAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Biological, GetResistance_BiologicalAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_CriticalHitResistance, GetResistance_CriticalHitAttribute);

	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Fire);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Ballistic);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Energy);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Kinetic);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Piercing);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Toxic);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Radiation);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Shock);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Digital);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Viral);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Sonic);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Psychological);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Nanite);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Acid);
	ResistanceAttributes.Add(GameplayTags.Attributes_Resistances_Biological);
	ResistanceAttributes.Add(GameplayTags.Attributes_CriticalHitResistance);

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Energy, COND_None, REPNOTIFY_Always);

	// Primary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Body, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Intellect, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Charisma, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_CyberAffinity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Perception, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Willpower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Primary_Luck, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_ArmorRating, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_Evasion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_Accuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_HackingPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_Persuasion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_Stealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Secondary_MaxEnergy, COND_None, REPNOTIFY_Always);

	// Resistances

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Fire, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Ballistic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Kinetic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Piercing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Toxic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Radiation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Shock, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Digital, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Viral, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Sonic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Psychological, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Nanite, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Acid, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Biological, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_CriticalHit, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetSecondary_MaxHealth());
	}

	if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetSecondary_MaxEnergy());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetSecondary_MaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}

	if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), 0.f, GetSecondary_MaxEnergy()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (LocalIncomingDamage > 0.f) 
		{
			const float Newhealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(Newhealth, 0.f, GetSecondary_MaxHealth()));

			bool bBlocked = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
			bool bCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);

			const bool bFatal = Newhealth <= 0.f;

			if (bFatal) 
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);

				if (CombatInterface) 
				{
					// Where the ability is going to
					AActor* TargetActor = Props.TargetAvatarActor.Get();
					// Where the ability is coming from
					AActor* SourceActor = Props.SourceAvatarActor.Get();

					// Calculate andle of impact and apply impulse
					if (TargetActor && SourceActor)
					{
						FVector ImpactVector = TargetActor->GetActorLocation() - SourceActor->GetActorLocation();
						ImpactVector.Normalize(); 
						CombatInterface->Die(ImpactVector, bBlocked, bCriticalHit);
					}
				}
			}
			else 
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
				Props.TargetAbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
			}
			
			ShowFloatingText(Props, LocalIncomingDamage, bBlocked, bCriticalHit);
		}
	}
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties Props, float Damage, bool isBlockingHit, bool bIsCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, isBlockingHit, bIsCriticalHit);
		}
	}
}


/*
 * Vital Attributes
 */

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Energy, OldEnergy);
}

/*
 * Primary Attributes Function
 */


void UAuraAttributeSet::OnRep_Primary_Body(const FGameplayAttributeData& OldBody)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Body, OldBody);
}

void UAuraAttributeSet::OnRep_Primary_Agility(const FGameplayAttributeData& OldAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Agility, OldAgility);
}

void UAuraAttributeSet::OnRep_Primary_Intellect(const FGameplayAttributeData& OldIntellect)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Intellect, OldIntellect);
}

void UAuraAttributeSet::OnRep_Primary_Charisma(const FGameplayAttributeData& OldCharisma)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Charisma, OldCharisma);
}

void UAuraAttributeSet::OnRep_Primary_CyberAffinity(const FGameplayAttributeData& OldCyberAffinity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_CyberAffinity, OldCyberAffinity);
}

void UAuraAttributeSet::OnRep_Primary_Perception(const FGameplayAttributeData& OldPerception)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Perception, OldPerception);
}

void UAuraAttributeSet::OnRep_Primary_Willpower(const FGameplayAttributeData& OldWillpower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Willpower, OldWillpower);
}

void UAuraAttributeSet::OnRep_Primary_Luck(const FGameplayAttributeData& OldLuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Primary_Luck, OldLuck);
}


/*
 * Secondary Attributes
 */

void UAuraAttributeSet::OnRep_Secondary_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_Stamina, OldStamina);
}

void UAuraAttributeSet::OnRep_Secondary_ArmorRating(const FGameplayAttributeData& OldArmorRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_ArmorRating, OldArmorRating);
}

void UAuraAttributeSet::OnRep_Secondary_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_Secondary_Evasion(const FGameplayAttributeData& OldEvasion)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_Evasion, OldEvasion);
}

void UAuraAttributeSet::OnRep_Secondary_Accuracy(const FGameplayAttributeData& OldAccuracy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_Accuracy, OldAccuracy);
}

void UAuraAttributeSet::OnRep_Secondary_CriticalChance(const FGameplayAttributeData& OldCriticalChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_CriticalChance, OldCriticalChance);
}

void UAuraAttributeSet::OnRep_Secondary_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_CriticalDamage, OldCriticalDamage);
}

void UAuraAttributeSet::OnRep_Secondary_HackingPower(const FGameplayAttributeData& OldHackingPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_HackingPower, OldHackingPower);
}

void UAuraAttributeSet::OnRep_Secondary_Persuasion(const FGameplayAttributeData& OldPersuasion)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_Persuasion, OldPersuasion);
}

void UAuraAttributeSet::OnRep_Secondary_Stealth(const FGameplayAttributeData& OldStealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_Stealth, OldStealth);
}

void UAuraAttributeSet::OnRep_Secondary_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Secondary_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Secondary_MaxEnergy, OldMaxEnergy);
}

/*
 * Resistance Attributes
 */

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Fire, OldFireResistance);
}

void UAuraAttributeSet::OnRep_BallisticResistance(const FGameplayAttributeData& OldBallisticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Ballistic, OldBallisticResistance);
}

void UAuraAttributeSet::OnRep_EnergyResistance(const FGameplayAttributeData& OldEnergyResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Energy, OldEnergyResistance);
}

void UAuraAttributeSet::OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Kinetic, OldKineticResistance);
}

void UAuraAttributeSet::OnRep_PiercingResistance(const FGameplayAttributeData& OldPiercingResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Piercing, OldPiercingResistance);
}

void UAuraAttributeSet::OnRep_ToxicResistance(const FGameplayAttributeData& OldToxicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Toxic, OldToxicResistance);
}

void UAuraAttributeSet::OnRep_RadiationResistance(const FGameplayAttributeData& OldRadiationResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Radiation, OldRadiationResistance);
}

void UAuraAttributeSet::OnRep_ShockResistance(const FGameplayAttributeData& OldShockResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Shock, OldShockResistance);
}

void UAuraAttributeSet::OnRep_DigitalResistance(const FGameplayAttributeData& OldDigitalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Digital, OldDigitalResistance);
}

void UAuraAttributeSet::OnRep_ViralResistance(const FGameplayAttributeData& OldViralResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Viral, OldViralResistance);
}

void UAuraAttributeSet::OnRep_SonicResistance(const FGameplayAttributeData& OldSonicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Sonic, OldSonicResistance);
}

void UAuraAttributeSet::OnRep_PsychologicalResistance(const FGameplayAttributeData& OldPsychologicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Psychological, OldPsychologicalResistance);
}

void UAuraAttributeSet::OnRep_NaniteResistance(const FGameplayAttributeData& OldNaniteResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Nanite, OldNaniteResistance);
}

void UAuraAttributeSet::OnRep_AcidResistance(const FGameplayAttributeData& OldAcidResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Acid, OldAcidResistance);
}

void UAuraAttributeSet::OnRep_BiologicalResistance(const FGameplayAttributeData& OldBiologicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Biological, OldBiologicalResistance);
}

void UAuraAttributeSet::OnRep_Resistance_CriticalHit(const FGameplayAttributeData& OldCriticalHitResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_CriticalHit, OldCriticalHitResistance);
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (!IsValid(Props.SourceAbilitySystemComponent) || !Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid()) return;

	Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
	Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

	if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
	{
		if (APawn* Pawn = Cast<APawn>(Props.SourceController))
		{
			Props.SourceController = Pawn->GetController();
		}
	}

	if (Props.SourceController)
	{
		Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
