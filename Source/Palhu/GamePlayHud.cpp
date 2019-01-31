// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"

void	UGameplayHUD::SetTimerText_Implementation(int TimerValue)
{
	Timer = FString::FromInt(TimerValue);
}