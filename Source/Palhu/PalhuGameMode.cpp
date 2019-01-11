// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PalhuGameMode.h"
#include "PalhuPawn.h"
#include "PalhuHud.h"

APalhuGameMode::APalhuGameMode()
{
	DefaultPawnClass = APalhuPawn::StaticClass();
	HUDClass = APalhuHud::StaticClass();
}
