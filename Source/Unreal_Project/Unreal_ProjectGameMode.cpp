// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_ProjectGameMode.h"
#include "Unreal_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_ProjectGameMode::AUnreal_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
