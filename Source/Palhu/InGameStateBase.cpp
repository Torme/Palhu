// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameStateBase.h"
#include "PrintDebug.h"
#include "UnrealNetwork.h"
#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"

AInGameStateBase::AInGameStateBase()
{
}

void	AInGameStateBase::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameStateBase, Timer);
}

void	AInGameStateBase::SetTimer(int newTimer)
{
	if (Role == ROLE_Authority)
	{
		Timer = newTimer;
	}
}

int AInGameStateBase::GetTimer()
{
	return Timer;
}

void AInGameStateBase::RestartAllPlayers()
{
	int i;

	for (i = 0; i < PlayerArray.Num(); i++)
	{
		print("RESET PLAYER");
		Cast<AGameplayGameMode>(AuthorityGameMode)->RestartPlayer(UGameplayStatics::GetPlayerController(GetWorld(), i));
	}
}