// Copyright Hungry Ghost


#include "Character/AuraEnemy.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include <Components/WidgetComponent.h>
#include "UI/Widget/AuraUserWidget.h"
#include "AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
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

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject())) {
		AuraUserWidget->SetWidgetController(this);
	}

	// Broadcast Health Changes to Blueprints to Update Health Bars
	auto AttributeSetClass = TSubclassOf<UAuraAttributeSet>(UAuraAttributeSet::StaticClass());
	
	if (const UAuraAttributeSet* AuraAttributes = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(AttributeSetClass))) {
		float StrengthAttribute = AuraAttributes->GetStrengthAttribute().GetNumericValue(AuraAttributes);
		float IntelligenceAttribute = AuraAttributes->GetIntelligenceAttribute().GetNumericValue(AuraAttributes);
		float ResilienceAttribute = AuraAttributes->GetResilienceAttribute().GetNumericValue(AuraAttributes);
		float VigorAttribute = AuraAttributes->GetVigorAttribute().GetNumericValue(AuraAttributes);

		UE_LOG(LogTemp, Warning, TEXT("Strength: %f"), StrengthAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Intelligence: %f"), IntelligenceAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Resilience: %f"), ResilienceAttribute);
		UE_LOG(LogTemp, Warning, TEXT("Vigor: %f"), VigorAttribute);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAuraEnemy::HitReactTagChanged);

		OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
	}
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();

}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
