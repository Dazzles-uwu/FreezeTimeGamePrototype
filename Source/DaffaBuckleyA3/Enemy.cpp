// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyProjectile.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set up the Tank Body with a default Static Mesh Component and attach it to the Root Component
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Body"));
	RootComponent = EnemyBody;
	
	/*EnemyBody->SetupAttachment(RootComponent);

	SetRootComponent(RootComponent);*/
	
	MovementSpeed = 150;
	EnemyRotationSpeed = 50;
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyProjectileBlueprint(TEXT("Blueprint'/Game/FirstPerson/Blueprints/BP_EnemyProjectile.BP_EnemyProjectile'"));
	if (EnemyProjectileBlueprint.Object){
		EnemyProjectileClass = EnemyProjectileBlueprint.Object->GeneratedClass;
	}

	Destroyed = false;
	CurrentTimer = 0;
	MaxTimer = 2;

	UE_LOG(LogTemp, Warning, TEXT("An enemy has been instantiated"));
}

void AEnemy::FireGun()
{
	//spawn bullet here
	FVector BulletSpawnOffset = FVector(0, 0, 80);

	BulletSpawnOffset = EnemyBody->GetComponentRotation().RotateVector(BulletSpawnOffset);
	
	FVector EnemyPosition = GetActorLocation();
	FVector StartPosition = BulletSpawnOffset + EnemyPosition;

	AEnemyProjectile* SpawnedBullet = (AEnemyProjectile*) GetWorld()->SpawnActor(EnemyProjectileClass, &StartPosition);

	SpawnedBullet->Parent = this;
	SpawnedBullet->SetActorRotation(EnemyBody->GetComponentRotation());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0));*/
	//LaunchCharacter(FVector(0,0,20), true, true);
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
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

