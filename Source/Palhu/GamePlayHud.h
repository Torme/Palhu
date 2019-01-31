// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class PALHU_API UGameplayHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
		void SetTimerText(int TimerValue);

	virtual void SetTimerText_Implementation(int TimerValue);

	UPROPERTY(BlueprintReadOnly)
		FString Timer;
};
