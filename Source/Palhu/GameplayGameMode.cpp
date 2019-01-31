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
}

void AGameplayGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNumPlayers() > 1)
	{
		ResetLevel();
		StartPlay();
		TimerComponent->Start();
		Cast<AInGameStateBase>(GameState)->RestartAllPlayers();
	}
}

void AGameplayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Cast<AInGameStateBase>(GameState)->SetTimer(TimerComponent->GetTimerValue());
	Cast<AInGameStateBase>(GameState)->CheckDeadPlayer();
}

//int AGameplayGameMode::GetTimerValue()
//{
//
//	return TimerComponent->GetTimerValue();
//}