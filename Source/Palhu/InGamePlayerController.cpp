// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"
#include "PrintDebug.h"

AInGamePlayerController::AInGamePlayerController()
{
	m_TeamIndex = 42;
}

bool AInGamePlayerController::SetTeamIndex_Validate(int newTeamIndex)
{
	return true;
}

void AInGamePlayerController::SetTeamIndex_Implementation(int newTeamIndex)
{
	printf("teamIndex: %d", newTeamIndex);
	m_TeamIndex = newTeamIndex;
}

int AInGamePlayerController::GetTeamIndex()
{
	//printf("Get team: %d", m_TeamIndex);
	return m_TeamIndex;
}