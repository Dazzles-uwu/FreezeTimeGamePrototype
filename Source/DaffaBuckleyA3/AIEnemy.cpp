// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "EnemyProjectile.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 5, 0);

	static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyProjectileBlueprint(TEXT("Blueprint'/Game/FirstPerson/Blueprints/BP_EnemyProjectile.BP_EnemyProjectile'"));
	if (EnemyProjectileBlueprint.Object){
		EnemyProjectileClass = EnemyProjectileBlueprint.Object->GeneratedClass;
	}

	DefaultWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
	ChasingWalkingSpeed = DefaultWalkingSpeed * 4;

	Destroyed = false;
	CurrentTimer = 0;
	MaxTimer = 2;
	
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = ChasingWalkingSpeed;
}

void AAIEnemy::ShootPlayer()
{
	FVector BulletSpawnOffset = FVector(0, 0, 80);

	BulletSpawnOffset = GetRootComponent()->GetComponentRotation().RotateVector(BulletSpawnOffset);
	
	FVector EnemyPosition = GetActorLocation();
	//FVector StartPosition = BulletSpawnOffset + EnemyPosition;

	AEnemyProjectile* SpawnedBullet = (AEnemyProjectile*) GetWorld()->SpawnActor(EnemyProjectileClass, &EnemyPosition);

	SpawnedBullet->Parent = this;
	SpawnedBullet->SetActorRotation(GetRootComponent()->GetComponentRotation());
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Destroyed)
	{
		CurrentTimer += DeltaTime;
		
		if (CurrentTimer >= MaxTimer)
		{
			Destroy();
		}
	}
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

