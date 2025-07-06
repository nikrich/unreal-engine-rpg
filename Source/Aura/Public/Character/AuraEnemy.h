// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;

DECLARE_MULTICAST_DELEGATE_TwoParams(F, const FGameplayTag, int32);

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;

	// Inherited via IEnemyInterface
	void HighlightActor() override;

	void UnhighlightActor() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Highlight")
	bool bIsHighlighted;

	/** Combat Interfact **/
	virtual int32 GetPlayerLevel() override { return Level; }
	/** End Combat Interfact **/

	UPROPERTY(BlueprintAssignable, Category = "Aura Enemy")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Aura Enemy")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Aura Enemy")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintReadOnly, Category = "Aura Enemy")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Aura Enemy")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura Enemy")
	float LifeSpan = 5.f;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void Die(FVector ImpactVector, bool bBlocked, bool bCriticalHit) override;

	ECharacterClass GetCharacterClass() const { return CharacterClass; }

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Bruiser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere,Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;	

	UPROPERTY()
	TObjectPtr<AAuraAIController> AIController;

};
