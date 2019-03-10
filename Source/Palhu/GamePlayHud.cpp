// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"
#include "PrintDebug.h"

void	UGameplayHUD::SetTimerText(int TimerValue)
{
	Timer = FString::FromInt(TimerValue);
}

void	UGameplayHUD::SetCurrentTeamScore(int TeamScore)
{
	CurrentTeamScore = FString::FromInt(TeamScore);
}

void	UGameplayHUD::SetOtherTeamScore(int TeamScore)
{
	OtherTeamScore = FString::FromInt(TeamScore);
}
