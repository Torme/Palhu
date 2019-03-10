// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"
#include "UnrealNetwork.h"
#include "PrintDebug.h"
#include "InGameStateBase.h"
#include "GamePlayHud.h"

AInGamePlayerController::AInGamePlayerController()
{
	m_TeamIndex = 42;
	m_Started = false;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{

		if (wGameHUD != nullptr)
		{
			m_GameHUD = CreateWidget<UUserWidget>(this, wGameHUD);

			if (m_GameHUD)
			{
				m_GameHUD->AddToViewport();
			}
		}
		m_Started = true;
	}
}

void AInGamePlayerController::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AInGamePlayerController, m_TeamIndex);
}

void AInGamePlayerController::SetTeamIndex(int newTeamIndex)
{
	m_TeamIndex = newTeamIndex;
}

int AInGamePlayerController::GetTeamIndex()
{
	return m_TeamIndex;
}

void AInGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	UGameplayHUD* GamePlayHUD;
	TArray<int> CurrentScores;

	if (m_Started)
	{
		GamePlayHUD = Cast<UGameplayHUD>(m_GameHUD);
		if (GamePlayHUD != nullptr && GetWorld())
		{
			GamePlayHUD->SetTimerText(GetWorld()->GetGameState<AInGameStateBase>()->GetTimer());
			CurrentScores = GetWorld()->GetGameState<AInGameStateBase>()->GetCurrentScores();
			for (int i = 0; i < CurrentScores.Num(); i++)
			{
				if (i == m_TeamIndex)
				{
					GamePlayHUD->SetCurrentTeamScore(CurrentScores[i]);
				}
				else
				{
					GamePlayHUD->SetOtherTeamScore(CurrentScores[i]);
				}
			}
		}
	}
}