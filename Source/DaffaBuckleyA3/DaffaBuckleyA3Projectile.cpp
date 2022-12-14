// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaffaBuckleyA3Projectile.h"

#include "AIController.h"
#include "AIEnemy.h"
#include "BlueprintEditor.h"
#include "Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADaffaBuckleyA3Projectile::ADaffaBuckleyA3Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADaffaBuckleyA3Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ADaffaBuckleyA3Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		
		Destroy();
	}
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("An Enemy has been hit") );
		
		FVector BulletDirection = GetActorForwardVector();

		if (Cast<AEnemy>(OtherActor))
		{
			if (Cast<AEnemy>(OtherActor)->EnemyBody)
			{
				Cast<AEnemy>(OtherActor)->EnemyBody->SetSimulatePhysics(true);
				Cast<AEnemy>(OtherActor)->LaunchCharacter(BulletDirection * 500, false, false);
				Cast<AEnemy>(OtherActor)->Destroyed = true;	
			}	
		}
		else if (Cast<AAIEnemy>(OtherActor)) 
		{
			if (Cast<AAIEnemy>(OtherActor)->GetMesh())
			{
				Cast<AAIEnemy>(OtherActor)->GetMesh()->SetSimulatePhysics(true);
				Cast<AAIEnemy>(OtherActor)->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				//Cast<AAIEnemy>(OtherActor)->GetMesh()->AddImpulse(FVector(0,0,500));
				Cast<AAIEnemy>(OtherActor)->Destroyed = true;
			}
			
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Character launched"));
	}
}
