// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class PALHU_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

	public:
		AInGameHUD();

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

		UPROPERTY(Category = TimerInfo, EditDefaultsOnly)
			UFont* TimerFont;
		UPROPERTY(Category = TimerInfo, EditDefaultsOnly)
			FVector2D TimerOffset;
		UPROPERTY(Category = TimerInfo, EditDefaultsOnly)
			FString TimerText;


	private:
		void UpdateValues();
		void DrawCrossHair();
		void DrawHealthBar();
		void DrawSpeedInfo();
		void DrawTimer();

		int m_MaxHeath;
		int m_CurrentHealth;
		float m_CurrentSpeed;
		int m_CurrentGear;
		int m_CurrentTimer;
	};
