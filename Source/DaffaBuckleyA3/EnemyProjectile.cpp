// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "DaffaBuckleyA3Character.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnBulletHit);
	RootComponent = BulletMesh;

	Parent = nullptr;

	MovementSpeed = 950;
	MaximumLifetime = 5;
	CurrentLifetime = 0;
	//UE_LOG(LogTemp, Warning, TEXT("A bullet is spawned"));

}

void AEnemyProjectile::OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		if(!Parent)
		{
			return;
		}
		if (Parent == OtherActor)
		{
			return;
		}
		if (Cast<ADaffaBuckleyA3Character>(OtherActor))
		{
			Cast<ADaffaBuckleyA3Character>(OtherActor)->ChangeHealth(HealthAlteration);
		}
		Destroy();
	}
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FVector Movement = (Forward * MovementSpeed * DeltaTime);
	FVector NewLocation = CurrentLocation + Movement;

	SetActorLocation(NewLocation);

	CurrentLifetime += DeltaTime;
	if(CurrentLifetime >= MaximumLifetime)
	{
		Destroy();
	}

}

