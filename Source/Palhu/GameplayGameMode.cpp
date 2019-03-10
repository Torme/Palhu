// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameMode.h"
#include "GameplayTimerComponent.h"
#include "PrintDebug.h"
#include "InGameStateBase.h"
#include "InGamePlayerController.h"

AGameplayGameMode::AGameplayGameMode()
{
	TimerComponent = CreateDefaultSubobject<UGameplayTimerComponent>(TEXT("TimerComponent"));
	AddOwnedComponent(TimerComponent);
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	m_GameStarted = false;
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	m_GameState = Cast<AInGameStateBase>(GameState);
}

void AGameplayGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNumPlayers() == 1)
		StartPlay();
	Cast<AInGamePlayerController>(NewPlayer)->SetTeamIndex(m_GameState->AddPlayer(NewPlayer));
	if (GetNumPlayers() > 1)
	{
		ResetLevel();
		TimerComponent->Start();
		m_GameState->RestartAllPlayers();
		m_GameStarted = true;
	}
}

void AGameplayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (m_GameStarted)
	{
		m_GameState->SetTimer(TimerComponent->GetTimerValue());
		m_GameState->CheckDeadPlayer();
	}
}

//int AGameplayGameMode::GetTimerValue()
//{
//
//	return TimerComponent->GetTimerValue();
//}