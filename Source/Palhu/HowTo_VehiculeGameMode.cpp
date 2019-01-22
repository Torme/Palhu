// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HowTo_VehiculeGameMode.h"
#include "HowTo_VehiculePawn.h"
#include "HowTo_VehiculeHud.h"

AHowTo_VehiculeGameMode::AHowTo_VehiculeGameMode()
{
	DefaultPawnClass = AHowTo_VehiculePawn::StaticClass();
	HUDClass = AHowTo_VehiculeHud::StaticClass();
}
