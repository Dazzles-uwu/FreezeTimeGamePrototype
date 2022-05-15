// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DaffaBuckleyA3Character.h"
#include "GameFramework/PlayerController.h"
#include "HumanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DAFFABUCKLEYA3_API AHumanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	ADaffaBuckleyA3Character* PlayerCharacter;

	void HawkEye();

	void HawkEyeCoolDown();

	void HawkEyeDeactivated();

	void HawkEyeActivated();
	
	void DoubleJump();

	void StopDoubleJump();

	void BulletCooldown();
	
	/** Fires a projectile. */
	void OnPrimaryAction();

private:
	FTimerHandle HawkEyeAbilityTimer;
	FTimerHandle ReloadTimer;

	int HawkEyeMultiplier;
	TArray<AActor*> TempActors;
};

