// Copyright Epic Games, Inc. All Rights Reserved.

#include "DropperGameMode.h"
#include "DropperCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADropperGameMode::ADropperGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
