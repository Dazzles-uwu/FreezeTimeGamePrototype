// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemy.generated.h"

UCLASS()
class DAFFABUCKLEYA3_API AAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemy();

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AEnemyProjectile> EnemyProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ShootPlayer();

	float DefaultWalkingSpeed;

	float ChasingWalkingSpeed;

	bool Destroyed;

	float CurrentTimer;
	float MaxTimer;

};
