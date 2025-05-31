// Copyright Hungry Ghost


#include "Character/AuraEnemy.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include <Components/WidgetComponent.h>
#include "UI/Widget/AuraUserWidget.h"
#include "AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/AuraAIController.h"
#include <AbilitySystem/AuraAbilitySystemLibrary.h>

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->CustomDepthStencilValue = 250;
	Weapon->CustomDepthStencilValue = 250;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet.Get());

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AAuraAIController* LocalAIController = Cast<AAuraAIController>(NewController);
}


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();

	if (HasAuthority()) 
	{
		UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}

	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject())) {
		AuraUserWidget->SetWidgetController(this);
	}

	// Broadcast Health Changes to Blueprints to Update Health Bars
	auto AttributeSetClass = TSubclassOf<UAuraAttributeSet>(UAuraAttributeSet::StaticClass());

	if (const UAuraAttributeSet* AuraAttributes = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(AttributeSetClass))) {
		float BodyAttribute = AuraAttributes->GetPrimary_BodyAttribute().GetNumericValue(AuraAttributes);
		float AgilityAttribute = AuraAttributes->GetPrimary_AgilityAttribute().GetNumericValue(AuraAttributes);
		float IntelligenceAttribute = AuraAttributes->GetPrimary_IntellectAttribute().GetNumericValue(AuraAttributes);
		float CharismaAttribute = AuraAttributes->GetPrimary_CharismaAttribute().GetNumericValue(AuraAttributes);
		float CyberAffinityAttribute = AuraAttributes->GetPrimary_CyberAffinityAttribute().GetNumericValue(AuraAttributes);
		float PerceptionAttribute = AuraAttributes->GetPrimary_PerceptionAttribute().GetNumericValue(AuraAttributes);
		float WillpowerAttribute = AuraAttributes->GetPrimary_WillpowerAttribute().GetNumericValue(AuraAttributes);
		float LuckAttribute = AuraAttributes->GetPrimary_LuckAttribute().GetNumericValue(AuraAttributes);
	
		UE_LOG(LogTemp, Warning, TEXT("Body: %f"), BodyAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Agility: %f"), AgilityAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Intelligence: %f"), IntelligenceAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Charisma: %f"), CharismaAttribute);
		UE_LOG(LogTemp, Warning, TEXT("CyberAffinity: %f"), CyberAffinityAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Perception: %f"), PerceptionAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Willpower: %f"), WillpowerAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Luck: %f"), LuckAttribute);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetSecondary_MaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAuraEnemy::HitReactTagChanged);

		OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributes->GetSecondary_MaxHealth());
	}
}

void AAuraEnemy::HighlightActor()
{
	// Set the custom depth stencil value to 1
	// This will make the actor render with the custom depth stencil value
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);

	bIsHighlighted = true;
}

void AAuraEnemy::UnhighlightActor()
{
	// Set the custom depth stencil value to 0
	// This will make the actor render normally
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	bIsHighlighted = false;
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;
}

void AAuraEnemy::Die(FVector ImpactVector, bool bBlocked, bool bCriticalHit)
{
	SetLifeSpan(LifeSpan);
	OnDeath.Broadcast();
	Super::Die(ImpactVector, bBlocked, bCriticalHit);
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority()) 
	{
		InitializeDefaultAttributes();
	}

}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
