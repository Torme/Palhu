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

	DrawCrossHair();
	DrawHealthBar();
	DrawSpeedInfo();
}

void AHowTo_VehiculeHud::DrawCrossHair()
{
	if (CrossHairTexture == nullptr)
		return;

	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D CrossHairDrawPosition(Center.X - (CrossHairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrossHairTexture->GetSurfaceHeight() * 0.5f));
	FCanvasTileItem TileItem(CrossHairDrawPosition, CrossHairTexture->Resource, FLinearColor::White);

	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AHowTo_VehiculeHud::DrawHealthBar()
{
	if (HealthBarBackgroundTexture == nullptr || HealthBarForegroundTexture == nullptr)
		return;
	FCanvasTileItem BackgroundTileItem(HealthBarOffset, HealthBarBackgroundTexture->Resource, HealthBarDimention, FLinearColor::White);
	FCanvasTileItem ForegroundTileItem(HealthBarOffset + HealthBarForegroundOffset, HealthBarForegroundTexture->Resource, HealthBarDimention - 2 * HealthBarForegroundOffset, FLinearColor::White);

	BackgroundTileItem.BlendMode = SE_BLEND_Translucent;
	ForegroundTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BackgroundTileItem);
	Canvas->DrawItem(ForegroundTileItem);
}

void AHowTo_VehiculeHud::DrawSpeedInfo()
{
	if (SpeedInfoFont == nullptr)
		return;
	FVector2D SpeedTextLocation(Canvas->ClipX - SpeedOffset.X, Canvas->ClipY - SpeedOffset.Y);
	FVector2D GearsTextLocation(Canvas->ClipX - GearsOffset.X, Canvas->ClipY - GearsOffset.Y);
	FCanvasTextItem SpeedTextItem(SpeedTextLocation, SpeedText, SpeedInfoFont, FLinearColor::White);
	FCanvasTextItem GearsTextItem(GearsTextLocation, GearsText, SpeedInfoFont, FLinearColor::White);

	SpeedTextItem.BlendMode = SE_BLEND_Translucent;
	GearsTextItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(SpeedTextItem);
	Canvas->DrawItem(GearsTextItem);
}

#undef LOCTEXT_NAMESPACE
