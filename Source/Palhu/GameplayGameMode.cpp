// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameMode.h"
#include "HUDComponent.h"

AGameplayGameMode::AGameplayGameMode()
{
	HUDComponent = CreateDefaultSubobject<UHUDComponent>(TEXT("TimerComponent"));
	AddOwnedComponent(HUDComponent);
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
		HUDComponent->StartGame();
		StartPlay();
	}
}
