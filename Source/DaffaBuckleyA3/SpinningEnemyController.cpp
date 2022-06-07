// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningEnemyController.h"

void ASpinningEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<AEnemy>(InPawn);

	if(PossessedEnemy)
	{
		CurrentTimer = 0;
		MaxTimer = 2.5;
	}
}

void ASpinningEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentTimer += DeltaSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("Calling EVERY TICK") );
	if (PossessedEnemy)
	{
		FRotator RotationAmount = FRotator(0, (PossessedEnemy->EnemyRotationSpeed * 13) * DeltaSeconds, 0);
		PossessedEnemy->AddActorLocalRotation(RotationAmount);
		
		if (CurrentTimer >= MaxTimer)
		{
			//Pseudo randomly fires
			float RandomNumber = rand() % 5 + 2;
			PossessedEnemy->FireGun();
			MaxTimer = RandomNumber;
			UE_LOG(LogTemp, Warning, TEXT("The random number value is: %f"), RandomNumber);
			CurrentTimer = 0;
		}
	}
}

void ASpinningEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	PossessedEnemy = nullptr;
	
}
