// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PALHU_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInGamePlayerController();

	int GetTeamIndex();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void SetTeamIndex(int newTeamIndex);
	void SetTeamIndex_Implementation(int newTeamIndex);
	bool SetTeamIndex_Validate(int newTeamIndex);

private:

	int m_TeamIndex;
};
