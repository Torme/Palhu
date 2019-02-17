// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameStateBase.h"
#include "PrintDebug.h"
#include "UnrealNetwork.h"
#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HowTo_VehiculePawn.h"
#include "HealthComponent.h"

AInGameStateBase::AInGameStateBase()
{
}

void	AInGameStateBase::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameStateBase, m_Timer);
}

void	AInGameStateBase::SetTimer(int newTimer)
{
	if (Role == ROLE_Authority)
	{
		m_Timer = newTimer;
	}
	m_Scores.Add(8);
}

int AInGameStateBase::GetTimer()
{
	return m_Timer;
}

void AInGameStateBase::AddPlayer(APlayerController* NewPlayer)
{
	m_Scores.Add(8);
}

void AInGameStateBase::RestartAllPlayers()
{
	int i;

	for (i = 0; i < PlayerArray.Num(); i++)
	{
		Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(UGameplayStatics::GetPlayerController(GetWorld(), i));
	}
}

void AInGameStateBase::CheckDeadPlayer()
{
	int i;
	//int oldScore;
	int aliveCount;
	APlayerController* PlayerController;

	aliveCount = 0;
	for (i = 0; i < PlayerArray.Num(); i++)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), i);
		if (PlayerController != nullptr)
		{
			if (PlayerController->GetPawn() == nullptr)
			{
				print("end!!!!!!!");
				/*oldScore = m_Scores[PlayerController->GetUniqueID()];
				if (oldScore > 0)
				{
					aliveCount++;
					m_Scores[PlayerController->GetUniqueID()] = oldScore - 1;
					Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(PlayerController);
				}*/
			}
		}
	}
	if (aliveCount <= 1)
	{
		/*print("end!!!!!!!");*/
	}

}