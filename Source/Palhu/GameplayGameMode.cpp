// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameMode.h"
#include "GameplayTimerComponent.h"
#include "PrintDebug.h"
#include "InGameStateBase.h"

AGameplayGameMode::AGameplayGameMode()
{
	TimerComponent = CreateDefaultSubobject<UGameplayTimerComponent>(TEXT("TimerComponent"));
	AddOwnedComponent(TimerComponent);
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	m_GameState = Cast<AInGameStateBase>(GameState);
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AGameplayGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	m_GameState->AddPlayer(NewPlayer);
	if (GetNumPlayers() > 1)
	{
		ResetLevel();
		StartPlay();
		TimerComponent->Start();
		m_GameState->RestartAllPlayers();
	}
}

void AGameplayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	m_GameState->SetTimer(TimerComponent->GetTimerValue());
	m_GameState->CheckDeadPlayer();
}

//int AGameplayGameMode::GetTimerValue()
//{
//
//	return TimerComponent->GetTimerValue();
//}