// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"
#include "UnrealNetwork.h"
#include "PrintDebug.h"

AInGamePlayerController::AInGamePlayerController()
{
	m_TeamIndex = 42;
}

void AInGamePlayerController::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AInGamePlayerController, m_TeamIndex);
}

void AInGamePlayerController::SetTeamIndex(int newTeamIndex)
{
	m_TeamIndex = newTeamIndex;
}

int AInGamePlayerController::GetTeamIndex()
{
	return m_TeamIndex;
}