// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1Base.h"

#include "HumanPlayerController.h"

ALevel1Base::ALevel1Base()
{
	PlayerControllerClass = AHumanPlayerController::StaticClass();
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
