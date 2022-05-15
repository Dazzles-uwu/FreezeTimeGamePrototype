// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "SpinningEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class DAFFABUCKLEYA3_API ASpinningEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnUnPossess() override;

protected:
	AEnemy* PossessedEnemy;
	float MaxShootDelay = 5;

	float CurrentTimer;
	float MaxTimer;
};
