// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

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

	UPROPERTY(BlueprintReadOnly, Category = "Aura Enemy")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Aura Enemy")
	float BaseWalkSpeed = 250.f;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;
};
