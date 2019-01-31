// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameMode.h"
#include "GameplayTimerComponent.h"
#include "Engine/Engine.h"

AGameplayGameMode::AGameplayGameMode()
{
	TimerComponent = CreateDefaultSubobject<UGameplayTimerComponent>(TEXT("TimerComponent"));
	AddOwnedComponent(TimerComponent);
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "start game");
}

void AGameplayGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNumPlayers() > 1)
	{
		StartPlay();
	}
}
