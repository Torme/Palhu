// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "HowTo_VehiculeHud.generated.h"


UCLASS(config = Game)
class AHowTo_VehiculeHud : public AHUD
{
	GENERATED_BODY()

public:
	AHowTo_VehiculeHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrossHairTexture;
};
