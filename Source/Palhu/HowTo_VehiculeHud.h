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

	virtual void DrawHUD() override;

protected:
	UPROPERTY(Category = CrossHair, EditDefaultsOnly)
	UTexture2D* CrossHairTexture;

	UPROPERTY(Category = HealthBar, EditDefaultsOnly)
	UTexture2D* HealthBarBackgroundTexture;
	UPROPERTY(Category = HealthBar, EditDefaultsOnly)
	UTexture2D* HealthBarForegroundTexture;
	UPROPERTY(Category = HealthBar, EditDefaultsOnly)
	FVector2D HealthBarDimention;
	UPROPERTY(Category = HealthBar, EditDefaultsOnly)
	FVector2D HealthBarForegroundOffset;
	UPROPERTY(Category = HealthBar, EditDefaultsOnly)
	FVector2D HealthBarOffset;
	
	UPROPERTY(Category = SpeedInfo, EditDefaultsOnly)
	UFont* SpeedInfoFont;
	UPROPERTY(Category = SpeedInfo, EditDefaultsOnly)
	FVector2D SpeedOffset;
	UPROPERTY(Category = SpeedInfo, EditDefaultsOnly)
	FVector2D GearsOffset;
	UPROPERTY(Category = SpeedInfo, EditDefaultsOnly)
	FString SpeedText;
	UPROPERTY(Category = SpeedInfo, EditDefaultsOnly)
	FString GearsText;

private:
	void UpdateValues();
	void DrawCrossHair();
	void DrawHealthBar();
	void DrawSpeedInfo();

	int m_MaxHeath;
	int m_CurrentHealth;
	float m_CurrentSpeed;
	int m_CurrentGear;
};
