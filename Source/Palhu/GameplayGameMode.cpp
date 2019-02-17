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
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	m_GameState = Cast<AInGameStateBase>(GameState);
	//StartPlay();
}

void AGameplayGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNumPlayers() == 1)
		StartPlay();
	m_GameState->AddPlayer(NewPlayer);
	if (GetNumPlayers() > 1)
	{
		ResetLevel();
		TimerComponent->Start();
		m_GameState->RestartAllPlayers();
	}
}

void AGameplayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Check if m_GameState can SetTimer (Crash UnrealEngine)
	m_GameState->SetTimer(TimerComponent->GetTimerValue());
	m_GameState->CheckDeadPlayer();
}

//int AGameplayGameMode::GetTimerValue()
//{
//
//	return TimerComponent->GetTimerValue();
//}