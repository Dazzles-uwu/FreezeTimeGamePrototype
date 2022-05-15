// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class DAFFABUCKLEYA3_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EnemyBody;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EnemyPlayer;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AEnemyProjectile> EnemyProjectileClass;

	UPROPERTY(EditAnywhere)
	float EnemyRotationSpeed;

	void FireGun();

	bool Destroyed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float CurrentTimer;
	float MaxTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
