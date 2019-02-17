// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameStateBase.generated.h"

UCLASS()
class PALHU_API AInGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY(Replicated)
	int m_Timer;

	//UPROPERTY(BlueprintReadOnly, Category = Test)
	TArray<uint32>	m_Scores;

public:
	AInGameStateBase();

	void	SetTimer(int newTimer);
	void	RestartAllPlayers();
	void	CheckDeadPlayer();
	int		GetTimer();
	void	AddPlayer(APlayerController* NewPlayer);

protected:
	virtual void GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const override;
	//virtual void BeginPlay() override;

private:
};
