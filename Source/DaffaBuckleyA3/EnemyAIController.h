// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DAFFABUCKLEYA3_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
		float SightRadius = 500;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
		float SightAge = 3.5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
		float LoseSightRadius = SightRadius + 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
		float FieldOfView = 45;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
		UAISenseConfig_Sight* SightConfiguration;

	UNavigationSystemV1* NavigationSystem;
	APawn* TargetPlayer;
};
