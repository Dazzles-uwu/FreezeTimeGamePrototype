// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerController.h"

#include "AIEnemy.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AHumanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind jump events
	InputComponent->BindAction("Jump", IE_Pressed, this, &AHumanPlayerController::DoubleJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AHumanPlayerController::StopDoubleJump);
	InputComponent->BindAction("HawkEye", IE_Pressed, this, &AHumanPlayerController::HawkEye);

	// Bind fire event
	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AHumanPlayerController::OnPrimaryAction);
}

void AHumanPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<ADaffaBuckleyA3Character>(InPawn);

	HawkEyeMultiplier = 5;
}

void AHumanPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHumanPlayerController::HawkEye()
{
	//REMEMBER TO GET RID OF TIMER ON UN-ONPOSSESS
	if (!GetWorld()->GetTimerManager().IsTimerActive(HawkEyeAbilityTimer))
	{
		HawkEyeActivated();
		GetWorld()->GetTimerManager().SetTimer(HawkEyeAbilityTimer, this, &AHumanPlayerController::HawkEyeCoolDown, 5, false);
	}
	else
	{
		HawkEyeDeactivated();
		GetWorld()->GetTimerManager().ClearTimer(HawkEyeAbilityTimer);
		UE_LOG(LogTemp, Warning, TEXT("HawkEyeDeactivated"));	
	}
	
}

void AHumanPlayerController::HawkEyeCoolDown()
{
	HawkEyeDeactivated();
	UE_LOG(LogTemp, Warning, TEXT("HawkEye Deactivated after 5 seconds"));	
	GetWorld()->GetTimerManager().ClearTimer(HawkEyeAbilityTimer);
}

void AHumanPlayerController::HawkEyeDeactivated()
{
	if (TempActors.Num() == 0)
	{
		//GET ALL ENEMY ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			Cast<AEnemy>(Temp)->MovementSpeed = Cast<AEnemy>(Temp)->MovementSpeed * HawkEyeMultiplier;
			Cast<AEnemy>(Temp)->EnemyRotationSpeed = Cast<AEnemy>(Temp)->EnemyRotationSpeed * HawkEyeMultiplier;
		}
		TempActors.Empty();

		//GET ALL BULLET ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyProjectile::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			Cast<AEnemyProjectile>(Temp)->MovementSpeed = Cast<AEnemyProjectile>(Temp)->MovementSpeed * HawkEyeMultiplier;
		}
		TempActors.Empty();

		//GET ALL ENEMY AI ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemy::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			Cast<AAIEnemy>(Temp)->GetCharacterMovement()->MaxWalkSpeed = Cast<AAIEnemy>(Temp)->GetCharacterMovement()->MaxWalkSpeed * (HawkEyeMultiplier * 3);
		}
		TempActors.Empty();
	}
}

void AHumanPlayerController::HawkEyeActivated()
{
	if (TempActors.Num() == 0)
	{
		//GET ALL ENEMY ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Original Float: %f"), Cast<AEnemy>(Temp)->MovementSpeed);
			Cast<AEnemy>(Temp)->MovementSpeed = Cast<AEnemy>(Temp)->MovementSpeed / HawkEyeMultiplier;
			Cast<AEnemy>(Temp)->EnemyRotationSpeed = Cast<AEnemy>(Temp)->EnemyRotationSpeed/ HawkEyeMultiplier;
			UE_LOG(LogTemp, Warning, TEXT("Changed Float: %f"), Cast<AEnemy>(Temp)->MovementSpeed);
		}
		TempActors.Empty();

		//GET ALL BULLET ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyProjectile::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			Cast<AEnemyProjectile>(Temp)->MovementSpeed = Cast<AEnemyProjectile>(Temp)->MovementSpeed / HawkEyeMultiplier;
		}
		TempActors.Empty();

		//GET ALL ENEMY AI ACTORS
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemy::StaticClass(), TempActors);
		for(auto Temp : TempActors)
		{
			Cast<AAIEnemy>(Temp)->GetCharacterMovement()->MaxWalkSpeed = Cast<AAIEnemy>(Temp)->GetCharacterMovement()->MaxWalkSpeed / (HawkEyeMultiplier * 3);
		}
		TempActors.Empty();
		UE_LOG(LogTemp, Warning, TEXT("HawkEyeActivated"));
			
	}
}


void AHumanPlayerController::DoubleJump()
{
	//PlayerCharacter->LaunchCharacter(FVector(0,0,1000), true, true);
	if (PlayerCharacter->JumpCurrentCount <= PlayerCharacter->JumpMaxCount )
	{
		PlayerCharacter->Jump();
		UE_LOG(LogTemp, Warning, TEXT("The jump count value is: %d"), PlayerCharacter->JumpCurrentCount);
		UE_LOG(LogTemp, Warning, TEXT("The jump max value is: %d"), PlayerCharacter->JumpMaxCount);
	}
}

void AHumanPlayerController::StopDoubleJump()
{
	if (PlayerCharacter->JumpCurrentCount >= 2)
	{
		PlayerCharacter->StopJumping();
	}
}

void AHumanPlayerController::BulletCooldown()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloaded complete after 1.5 seconds"));
	//Clears the timer after 3 seconds
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
}

void AHumanPlayerController::OnPrimaryAction()
{
	//REMEMBER TO GET RID OF TIMER ON UN-ONPOSSESS
	if (!GetWorld()->GetTimerManager().IsTimerActive(ReloadTimer))
	{
		// Trigger the OnItemUsed Event
		PlayerCharacter->OnUseItem.Broadcast();
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AHumanPlayerController::BulletCooldown, 1.5, false);
	}
	
}
