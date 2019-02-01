// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"

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
#include "InGameStateBase.h"
#include "PrintDebug.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();

	UpdateValues();
	DrawCrossHair();
	DrawHealthBar();
	DrawSpeedInfo();
	DrawTimer();
}

void AInGameHUD::UpdateValues()
{
	AHowTo_VehiculePawn* Player;
	AInGameStateBase* GameState;

	Player = Cast<AHowTo_VehiculePawn>(GetOwningPawn());
	if (Player != nullptr)
	{
		m_MaxHeath = Player->GetMaxHealth();
		m_CurrentHealth = Player->GetCurrentHealth();
		m_CurrentSpeed = Player->GetCurrentSpeed();
		m_CurrentGear = Player->GetCurrentGear();
		if (GetWorld() != nullptr)
		{
			GameState = Cast<AInGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
			if (GameState != nullptr)
			{
				m_CurrentTimer = GameState->GetTimer();
			}
		}
	}
}

void AInGameHUD::DrawCrossHair()
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

void AInGameHUD::DrawHealthBar()
{
	FVector2D ForegroundPosition;
	FVector2D ForegroundDimention;

	if (HealthBarBackgroundTexture == nullptr || HealthBarForegroundTexture == nullptr)
		return;
	ForegroundPosition = HealthBarOffset + HealthBarForegroundOffset;
	ForegroundDimention = HealthBarDimention - 2 * HealthBarForegroundOffset;
	ForegroundDimention.X *= m_MaxHeath == 0 ? 0 : static_cast<float>(m_CurrentHealth) / static_cast<float>(m_MaxHeath);
	FCanvasTileItem BackgroundTileItem(HealthBarOffset, HealthBarBackgroundTexture->Resource, HealthBarDimention, FLinearColor::White);
	FCanvasTileItem ForegroundTileItem(ForegroundPosition, HealthBarForegroundTexture->Resource, ForegroundDimention, FLinearColor::White);

	BackgroundTileItem.BlendMode = SE_BLEND_Translucent;
	ForegroundTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BackgroundTileItem);
	Canvas->DrawItem(ForegroundTileItem);
}

void AInGameHUD::DrawSpeedInfo() 
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

void AInGameHUD::DrawTimer()
{
	FText TimerText;
	FVector2D TimerTextLocation;

	if (TimerFont == nullptr)
		return;
	TimerText = FText::FromString(FString::FromInt(m_CurrentTimer));
	TimerTextLocation= FVector2D(Canvas->ClipX - TimerOffset.X, Canvas->ClipY - TimerOffset.Y);
	FCanvasTextItem TimerTextItem(TimerTextLocation, TimerText, TimerFont, FLinearColor::White);

	TimerTextItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TimerTextItem);
}

#undef LOCTEXT_NAMESPACE
