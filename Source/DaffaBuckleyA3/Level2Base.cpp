// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2Base.h"

#include "HumanPlayerController.h"

ALevel2Base::ALevel2Base()
{
	PlayerControllerClass = AHumanPlayerController::StaticClass();
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
