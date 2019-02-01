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
}

int AInGameStateBase::GetTimer()
{
	return m_Timer;
}

void AInGameStateBase::AddPlayer(APlayerController* NewPlayer)
{
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
	APlayerController* PlayerController;

	for (i = 0; i < PlayerArray.Num(); i++)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), i);
		if (PlayerController != nullptr)
		{
			if (PlayerController->GetPawn() == nullptr)
			{
				Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(PlayerController);
			}
		}
	}

}