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

	UPROPERTY()
	UFont* HUDFont;

	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrossHairTexture;
};
