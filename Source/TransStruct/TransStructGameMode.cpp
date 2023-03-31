// Copyright Epic Games, Inc. All Rights Reserved.

#include "TransStructGameMode.h"
#include "TransStructCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATransStructGameMode::ATransStructGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
