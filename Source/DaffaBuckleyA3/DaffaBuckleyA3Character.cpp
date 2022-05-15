// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaffaBuckleyA3Character.h"
#include "DaffaBuckleyA3Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// ADaffaBuckleyA3Character

ADaffaBuckleyA3Character::ADaffaBuckleyA3Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void ADaffaBuckleyA3Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	JumpMaxCount = 2;
}

void ADaffaBuckleyA3Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *GetActorLocation().ToString());
}

//////////////////////////////////////////////////////////////////////////// Input

void ADaffaBuckleyA3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ADaffaBuckleyA3Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ADaffaBuckleyA3Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ADaffaBuckleyA3Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ADaffaBuckleyA3Character::LookUpAtRate);
}

void ADaffaBuckleyA3Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		//OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ADaffaBuckleyA3Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ADaffaBuckleyA3Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADaffaBuckleyA3Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADaffaBuckleyA3Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ADaffaBuckleyA3Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool ADaffaBuckleyA3Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADaffaBuckleyA3Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ADaffaBuckleyA3Character::EndTouch);

		return true;
	}
	
	return false;
}

void ADaffaBuckleyA3Character::ChangeHealth(int Amount)
{
	if (Health != 0)
	{
	    UE_LOG(LogTemp, Warning, TEXT("Health before lost: %d"), Health);
		Health -= Amount;
		UE_LOG(LogTemp, Warning, TEXT("Health after lost: %d"), Health);

		//TO BE CHANGED TO GAME OVER SCREEN IF PLAYER DIES
		if (Health <= 0)
		{
			Health = 10;
		}
	}
}
