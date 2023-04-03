// Copyright Epic Games, Inc. All Rights Reserved.

#include "AKP_ProjectGameMode.h"
#include "AKP_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAKP_ProjectGameMode::AAKP_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
