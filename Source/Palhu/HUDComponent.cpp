// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDComponent.h"
#include "Engine/Engine.h"
#include "GamePlayHud.h"
#include "GameplayTimerComponent.h"

// Sets default values for this component's properties
UHUDComponent::UHUDComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (!StartingTimerValue)
	{
		StartingTimerValue = 600;
	}
}


// Called when the game starts
void UHUDComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GameWidget != nullptr)
	{
		MyGameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidget);
		if (MyGameWidget)
		{
			MyGameWidget->AddToViewport();
		}
	}
}


// Called every frame
void UHUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, TEXT("TICK"));
	if (TimerValue > 0)
	{
		TimerValue -= DeltaTime;
	}
	if (MyGameWidget != nullptr)
	{
		Cast<UGameplayHUD>(MyGameWidget)->SetTimerText(TimerValue);
	}
}

void UHUDComponent::StartGame()
{
	TimerValue = StartingTimerValue;
}