// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"
#include "DaffaBuckleyA3Character.h"

// Sets default values
APressurePad::APressurePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Every Actor contains a root component. We initialize this as a scene component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	// We create a mesh that will be our visual representation of the object and attach it to the root
    PressurePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    PressurePadMesh->SetupAttachment(RootComponent);

	// We create a hitbox that will be our collider that we can walk over to activate. This is also attached to root
	PressurePadHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox Component"));
	PressurePadHitBox->SetupAttachment(RootComponent);

	TeleportableLocations.Add(FVector(177,2248,98));
	TeleportableLocations.Add(FVector(2828,1708,298));
	TeleportableLocations.Add(FVector(2488,564,198));
	TeleportableLocations.Add(FVector(2844,1362,98));
	TeleportableLocations.Add(FVector(1562,1710,98));
	TeleportableLocations.Add(FVector(2602,3344,98));
	TeleportableLocations.Add(FVector(1080,3286,98));
	TeleportableLocations.Add(FVector(868,2812,298));
	TeleportableLocations.Add(FVector(2600,2055,98));
	TeleportableLocations.Add(FVector(1832,1022,298));
}

void APressurePad::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Has Begun"));

		if (Cast<ADaffaBuckleyA3Character>(OtherActor)->IsPlayerControlled())
		{
			int RandomNumber = rand() % TeleportableLocations.Num();
			UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), RandomNumber);
			OtherActor->SetActorLocation(TeleportableLocations[RandomNumber]);
		}
	}
}

// Called when the game starts or when spawned
void APressurePad::BeginPlay()
{
	Super::BeginPlay();

	PressurePadHitBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePad::OnHitboxOverlapBegin);
}

// Called every frame
void APressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

