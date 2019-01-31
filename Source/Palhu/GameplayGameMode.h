// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

class UHUDComponent;

UCLASS()
class PALHU_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplayGameMode();
protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere)
		UHUDComponent *HUDComponent;
};
