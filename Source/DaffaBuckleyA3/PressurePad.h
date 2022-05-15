// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PressurePad.generated.h"

// We declare our own custom event that we will be activating
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressurePadActivated);


UCLASS()
class DAFFABUCKLEYA3_API APressurePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePad();

	UPROPERTY(BlueprintAssignable)
		FOnPressurePadActivated PressurePadHitBoxDelegate;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PressurePadMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* PressurePadHitBox;

	UFUNCTION()
    void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<FVector> TeleportableLocations;

};
