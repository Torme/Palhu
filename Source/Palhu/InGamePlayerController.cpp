// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"
#include "PrintDebug.h"
#include "HowTo_VehiculePawn.h"

AInGamePlayerController::AInGamePlayerController()
{
	m_Initialized = false;
}

void AInGamePlayerController::SetTeamIndex(int newTeamIndex)
{
	AHowTo_VehiculePawn	*CurrentPawn = Cast<AHowTo_VehiculePawn>(GetPawn());
	m_Initialized = true;
	if (CurrentPawn != nullptr)
	{
		CurrentPawn->SetTeamIndex(newTeamIndex);
	}
}

int AInGamePlayerController::GetTeamIndex()
{
	if (m_Initialized)
	{
		AHowTo_VehiculePawn	*CurrentPawn = Cast<AHowTo_VehiculePawn>(GetPawn());
		if (CurrentPawn != nullptr)
		{
			return CurrentPawn->GetTeamIndex();
		}
	}
	return 42;
}