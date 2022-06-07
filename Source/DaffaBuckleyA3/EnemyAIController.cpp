// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfiguration->SightRadius = SightRadius;
    SightConfiguration->LoseSightRadius = LoseSightRadius;
    SightConfiguration->PeripheralVisionAngleDegrees = FieldOfView;
    SightConfiguration->SetMaxAge(SightAge);
    SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
    SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfiguration->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfiguration);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPawnDetected);
	TargetPlayer = nullptr;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	if(NavigationSystem)
	{
		FNavLocation ReturnLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 2000,ReturnLocation);
		MoveToLocation(ReturnLocation.Location);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AEnemyAIController::GetControlRotation() const
{
	Super::GetControlRotation();

	if(GetPawn())
    {
     return FRotator(0, GetPawn()->GetActorRotation().Yaw, 0);
    }
    return FRotator::ZeroRotator;

}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if(NavigationSystem)
	{
		FNavLocation ReturnLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(),
	   2000,ReturnLocation);
		MoveToLocation(ReturnLocation.Location);
	}
}

void AEnemyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for(auto TempActor : DetectedPawns)
	{
		APawn* TempPawn = Cast<APawn>(TempActor);
		if(TempPawn)
		{
			if(TargetPlayer && TargetPlayer == TempPawn)
			{
				UE_LOG(LogTemp, Warning, TEXT("Player is known and is now leaving target space"));
				TargetPlayer = nullptr;
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player has been spotted. Saving reference"));
				TargetPlayer = TempPawn;
			}
		}
	}
}
