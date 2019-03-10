// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameStateBase.h"
#include "PrintDebug.h"
#include "UnrealNetwork.h"
#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HowTo_VehiculePawn.h"
#include "HealthComponent.h"
#include "InGamePlayerController.h"

AInGameStateBase::AInGameStateBase()
{
	FTeam TeamA;
	FTeam TeamB;

	TeamA.Name = "A";
	TeamA.Score = 2;
	TeamB.Name = "B";
	TeamB.Score = 2;
	m_Teams.Add(TeamA);
	m_Teams.Add(TeamB);
}


void	AInGameStateBase::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameStateBase, m_Timer);
	DOREPLIFETIME(AInGameStateBase, m_Teams);
}

void	AInGameStateBase::SetTimer(int newTimer)
{
	if (Role == ROLE_Authority)
	{
		m_Timer = newTimer;
	}
}

int AInGameStateBase::GetTimer()
{
	return m_Timer;
}

TArray<int> AInGameStateBase::GetCurrentScores()
{
	TArray<int> CurrentScores;

	for (int i = 0; i < m_Teams.Num(); i++)
	{
		CurrentScores.Add(m_Teams[i].Score);
	}
	return CurrentScores;
}

int AInGameStateBase::AddPlayer(APlayerController* NewPlayer)
{
	int teamIndex = 0;
	for (int i = 0; i < m_Teams.Num(); i++)
	{
		if (m_Teams[i].Players.Num() < m_Teams[teamIndex].Players.Num()) {
			teamIndex = i;
		}
	}
	m_Teams[teamIndex].Players.Add(NewPlayer);
	return teamIndex;
	Cast<AInGamePlayerController>(NewPlayer)->SetTeamIndex(teamIndex);
}

void AInGameStateBase::RestartAllPlayers()
{
	int i;

	for (i = 0; i < PlayerArray.Num(); i++)
	{
		Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(UGameplayStatics::GetPlayerController(GetWorld(), i));
	}
}

bool AInGameStateBase::CheckDeadPlayer_Validate()
{
	return true;
}

void AInGameStateBase::CheckDeadPlayer_Implementation()
{
	int i;
	int oldScore;
	int aliveCount;
	APlayerController* PlayerController;

	aliveCount = 0;
	for (i = 0; i < PlayerArray.Num(); i++)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), i);
		if (PlayerController != nullptr)
		{
			printf("team: %d", Cast<AInGamePlayerController>(PlayerController)->GetTeamIndex());
			if (PlayerController->GetPawn() == nullptr)
			{
				oldScore = m_Teams[Cast<AInGamePlayerController>(PlayerController)->GetTeamIndex()].Score;
				if (oldScore > 0)
				{
					aliveCount++;
					m_Teams[Cast<AInGamePlayerController>(PlayerController)->GetTeamIndex()].Score = oldScore - 1;
					Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(PlayerController);
				}
			}
			else
			{
				aliveCount++;
			}
		}
	}
	if (aliveCount <= 1)
	{
		print("end :)");
	}

}