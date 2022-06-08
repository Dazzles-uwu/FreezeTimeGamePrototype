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
	//GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPawnDetected);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnSensesUpdated);
	TargetPlayer = nullptr;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	if(!AIBlackboard)
		return;
	if(!ensure(BehaviorTree))
		return;
	
	UseBlackboard(AIBlackboard, BlackboardComponent);
	RunBehaviorTree(BehaviorTree);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedAIEnemy = Cast<AAIEnemy>(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(TargetPlayer)
    {
		BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());
    }

	/*if (PossessedAIEnemy)
	{
		if (BlackboardComponent->GetValueAsBool("ChasePlayer") == true)
		{
			PossessedAIEnemy->ShootPlayer();
		}
	}*/

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
}


void AEnemyAIController::GenerateNewRandomLocation()
{
	 if(NavigationSystem)
     {
	     FNavLocation ReturnLocation;
	     NavigationSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 2000, ReturnLocation);
	     BlackboardComponent->SetValueAsVector("PatrolPoint", ReturnLocation.Location);
     }

}

void AEnemyAIController::ShootBullet()
{
	if (PossessedAIEnemy)
	{
		PossessedAIEnemy->ShootPlayer();
	}
}

void AEnemyAIController::OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	APawn* TemporaryPawn = Cast<APawn>(UpdatedActor);
	if(TemporaryPawn && TemporaryPawn->IsPlayerControlled())
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Set Actor Location"));
			TargetPlayer = TemporaryPawn;
			BlackboardComponent->SetValueAsBool("ChasePlayer", true);
			BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());
		} else
		{
			TargetPlayer = nullptr;
			BlackboardComponent->ClearValue("ChasePlayer");
		}
	}
}
