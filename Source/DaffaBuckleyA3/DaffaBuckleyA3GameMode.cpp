// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaffaBuckleyA3GameMode.h"
#include "DaffaBuckleyA3Character.h"
#include "HumanPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ADaffaBuckleyA3GameMode::ADaffaBuckleyA3GameMode()
	: Super()
{

	PlayerControllerClass = AHumanPlayerController::StaticClass();
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
