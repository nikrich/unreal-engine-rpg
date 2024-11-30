// Copyright Hungry Ghost

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chacracter Class Defaults")
	int32 Level = 1;

};
