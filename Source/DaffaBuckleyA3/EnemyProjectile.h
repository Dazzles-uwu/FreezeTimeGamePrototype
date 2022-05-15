// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class DAFFABUCKLEYA3_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(EditAnywhere)
	AActor* Parent;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere)
	float MaximumLifetime;
	
	UPROPERTY(EditAnywhere)
	float CurrentLifetime;
	
	UPROPERTY(EditAnywhere)
	int HealthAlteration = 1;

	UFUNCTION() void OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
