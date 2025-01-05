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

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Strength);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Intelligence);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Resilience);
	PrimaryAttributes.Add(GameplayTags.Attributes_Primary_Vigor);

	/**
	 * Secondary Attributes
	 */

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_Armor);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth);
	SecondaryAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana);

	/**
	 * Resistances
	 */

	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Ballistic, GetBallisticResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Energy, GetEnergyResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Kinetic, GetKineticResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Piercing, GetPiercingResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Toxic, GetToxicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Radiation, GetRadiationResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Shock, GetShockResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Digital, GetDigitalResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Viral, GetViralResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Sonic, GetSonicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Psychological, GetPsychologicalResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Nanite, GetNaniteResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Acid, GetAcidResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistances_Biological, GetBiologicalResistanceAttribute);

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

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	// Primary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Resistances

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BallisticResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, EnergyResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, KineticResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PiercingResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ToxicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, RadiationResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ShockResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, DigitalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ViralResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, SonicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PsychologicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, NaniteResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, AcidResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BiologicalResistance, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (LocalIncomingDamage > 0.f) 
		{
			const float Newhealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(Newhealth, 0.f, GetMaxHealth()));

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

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

/*
 * Primary Attributes Function
 */

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

/*
 * Secondary Attributes
 */

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

/*
 * Resistance Attributes
 */

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResistance, OldFireResistance);
}

void UAuraAttributeSet::OnRep_BallisticResistance(const FGameplayAttributeData& OldBallisticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BallisticResistance, OldBallisticResistance);
}

void UAuraAttributeSet::OnRep_EnergyResistance(const FGameplayAttributeData& OldEnergyResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, EnergyResistance, OldEnergyResistance);
}

void UAuraAttributeSet::OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, KineticResistance, OldKineticResistance);
}

void UAuraAttributeSet::OnRep_PiercingResistance(const FGameplayAttributeData& OldPiercingResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PiercingResistance, OldPiercingResistance);
}

void UAuraAttributeSet::OnRep_ToxicResistance(const FGameplayAttributeData& OldToxicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ToxicResistance, OldToxicResistance);
}

void UAuraAttributeSet::OnRep_RadiationResistance(const FGameplayAttributeData& OldRadiationResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, RadiationResistance, OldRadiationResistance);
}

void UAuraAttributeSet::OnRep_ShockResistance(const FGameplayAttributeData& OldShockResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ShockResistance, OldShockResistance);
}

void UAuraAttributeSet::OnRep_DigitalResistance(const FGameplayAttributeData& OldDigitalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, DigitalResistance, OldDigitalResistance);
}

void UAuraAttributeSet::OnRep_ViralResistance(const FGameplayAttributeData& OldViralResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ViralResistance, OldViralResistance);
}

void UAuraAttributeSet::OnRep_SonicResistance(const FGameplayAttributeData& OldSonicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, SonicResistance, OldSonicResistance);
}

void UAuraAttributeSet::OnRep_PsychologicalResistance(const FGameplayAttributeData& OldPsychologicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PsychologicalResistance, OldPsychologicalResistance);
}

void UAuraAttributeSet::OnRep_NaniteResistance(const FGameplayAttributeData& OldNaniteResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, NaniteResistance, OldNaniteResistance);
}

void UAuraAttributeSet::OnRep_AcidResistance(const FGameplayAttributeData& OldAcidResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, AcidResistance, OldAcidResistance);
}

void UAuraAttributeSet::OnRep_BiologicalResistance(const FGameplayAttributeData& OldBiologicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BiologicalResistance, OldBiologicalResistance);
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
