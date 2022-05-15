// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingEnemyController.h"

#include "InterchangeResult.h"

void APatrollingEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<AEnemy>(InPawn);

	if(PossessedEnemy)
	{
		PatrolPoints.Empty();

		FVector CurrentLocation = PossessedEnemy->GetActorLocation();

		PatrolPoints.Add(CurrentLocation + FVector(500, 0, 0));
		PatrolPoints.Add(CurrentLocation + FVector(-500, 0, 0));
	}
}

void APatrollingEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//UE_LOG(LogTemp, Warning, TEXT("FIRED GUN") );

	if (PossessedEnemy && PatrolPoints.Num() > 0)
	{
		FVector CurrentLocation = PossessedEnemy->GetActorLocation();
		FVector DirectionToGoal = PatrolPoints[CurrentLocationIndex] - CurrentLocation;
		DirectionToGoal.Normalize();

		FVector ActorForwardVector = PossessedEnemy->GetActorForwardVector();
	
		float AngleBetweenPoints = FMath::RadiansToDegrees(acosf(FVector::DotProduct(ActorForwardVector, DirectionToGoal)));

		if (AngleBetweenPoints != 0)
		{
			FVector CrossProduct = FVector::CrossProduct(ActorForwardVector,DirectionToGoal);
			
			//FVector ResultantVector = DirectionToGoal - ActorForwardVector;

			float RotationAngle = PossessedEnemy->EnemyRotationSpeed * DeltaSeconds;
			
			
			if (RotationAngle > AngleBetweenPoints)
			{
				RotationAngle = AngleBetweenPoints;
				if (PossessedEnemy)
				{
					PossessedEnemy->FireGun();
				}
			}
	
			if (CrossProduct.Y < 0)
			{
				PossessedEnemy->AddActorLocalRotation(FRotator(0, RotationAngle, 0));
			}
			else {
				PossessedEnemy->AddActorLocalRotation(FRotator(0, -RotationAngle, 0));
			}
			
			return;
		}
		
		
		//FVector RotationMovement = ActorRotation.RotateVector()
		double DistanceToGoal = FVector::Distance(CurrentLocation, PatrolPoints[CurrentLocationIndex]);
		
		double MoveDistance = (PossessedEnemy->MovementSpeed * DeltaSeconds);
	
		CurrentLocation += MoveDistance * DirectionToGoal;
		
		if (MoveDistance > DistanceToGoal)
		{
			//PossessedEnemy->SetActorRotation(FRotator(0,180,0));
			CurrentLocation = PatrolPoints[CurrentLocationIndex];
			CurrentLocationIndex++;

			if (CurrentLocationIndex >= PatrolPoints.Num())
			{
				CurrentLocationIndex = 0;
			}
		}
		
		PossessedEnemy->SetActorLocation(CurrentLocation);
	}
}

void APatrollingEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	PossessedEnemy = nullptr;
}

void APatrollingEnemyController::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocationIndex = 0;
}
