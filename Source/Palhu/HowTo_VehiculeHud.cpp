// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HowTo_VehiculeHud.h"
#include "HowTo_VehiculePawn.h"
#include "WheeledVehicle.h"
#include "RenderResource.h"
#include "Shader.h"
#include "Engine/Canvas.h"
#include "WheeledVehicleMovementComponent.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

AHowTo_VehiculeHud::AHowTo_VehiculeHud()
{
}

void AHowTo_VehiculeHud::DrawHUD()
{
	Super::DrawHUD();

	UpdateValues();
	DrawCrossHair();
	DrawHealthBar();
	DrawSpeedInfo();
}

void AHowTo_VehiculeHud::UpdateValues()
{
	AHowTo_VehiculePawn* Player;

	Player = Cast<AHowTo_VehiculePawn>(GetOwningPawn());
	if (Player != nullptr)
	{
		m_MaxHeath = Player->GetMaxHealth();
		m_CurrentHealth = Player->GetCurrentHealth();
		m_CurrentSpeed = Player->GetCurrentSpeed();
		m_CurrentGear = Player->GetCurrentGear();
	}
}

void AHowTo_VehiculeHud::DrawCrossHair()
{
	FVector2D Center;
	FVector2D CrossHairDrawPosition;

	if (CrossHairTexture == nullptr)
		return;

	Center = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	CrossHairDrawPosition = FVector2D(Center.X - (CrossHairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrossHairTexture->GetSurfaceHeight() * 0.5f));
	FCanvasTileItem TileItem(CrossHairDrawPosition, CrossHairTexture->Resource, FLinearColor::White);

	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AHowTo_VehiculeHud::DrawHealthBar()
{
	FVector2D ForegroundPosition;
	FVector2D ForegroundDimention;

	if (HealthBarBackgroundTexture == nullptr || HealthBarForegroundTexture == nullptr)
		return;
	ForegroundPosition = HealthBarOffset + HealthBarForegroundOffset;
	ForegroundDimention = HealthBarDimention - 2 * HealthBarForegroundOffset;
	ForegroundDimention.X *= m_MaxHeath == 0 ? 0 : m_CurrentHealth / m_MaxHeath;
	FCanvasTileItem BackgroundTileItem(HealthBarOffset, HealthBarBackgroundTexture->Resource, HealthBarDimention, FLinearColor::White);
	FCanvasTileItem ForegroundTileItem(ForegroundPosition, HealthBarForegroundTexture->Resource, ForegroundDimention, FLinearColor::White);

	BackgroundTileItem.BlendMode = SE_BLEND_Translucent;
	ForegroundTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BackgroundTileItem);
	Canvas->DrawItem(ForegroundTileItem);
}

void AHowTo_VehiculeHud::DrawSpeedInfo()
{
	FText SpeedCompleteText;
	FText GearCompleteText;
	FVector2D SpeedTextLocation;
	FVector2D GearsTextLocation;

	if (SpeedInfoFont == nullptr)
		return;
	SpeedCompleteText = FText::FromString(FString::FromInt(m_CurrentSpeed) + SpeedText);
	GearCompleteText = FText::FromString(FString::FromInt(m_CurrentGear) + GearsText);
	SpeedTextLocation = FVector2D(Canvas->ClipX - SpeedOffset.X, Canvas->ClipY - SpeedOffset.Y);
	GearsTextLocation = FVector2D(Canvas->ClipX - GearsOffset.X, Canvas->ClipY - GearsOffset.Y);
	FCanvasTextItem SpeedTextItem(SpeedTextLocation, SpeedCompleteText, SpeedInfoFont, FLinearColor::White);
	FCanvasTextItem GearsTextItem(GearsTextLocation, GearCompleteText, SpeedInfoFont, FLinearColor::White);

	SpeedTextItem.BlendMode = SE_BLEND_Translucent;
	GearsTextItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(SpeedTextItem);
	Canvas->DrawItem(GearsTextItem);
}

#undef LOCTEXT_NAMESPACE
