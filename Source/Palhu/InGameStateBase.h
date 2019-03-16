// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameStateBase.generated.h"

USTRUCT()
struct FTeam
{
	GENERATED_USTRUCT_BODY()

	TArray<APlayerController* > Players;

	UPROPERTY()
	uint32 Score;

	UPROPERTY()
	FString Name;
};

UCLASS()
class PALHU_API AInGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY(Replicated)
	int m_Timer;

	//UPROPERTY(BlueprintReadOnly, Category = Test)

	UPROPERTY(Replicated)
	TArray<FTeam>	m_Teams;

public:
	AInGameStateBase();

	void	SetTimer(int newTimer);
	void	RestartAllPlayers();

	UFUNCTION(Server, Reliable, WithValidation)
	void	CheckDeadPlayer();
	bool	CheckDeadPlayer_Validate();
	void	CheckDeadPlayer_Implementation();

	int		GetTimer();
	TArray<int>		GetCurrentScores();
	void	AddPlayer(APlayerController* NewPlayer);

	FORCEINLINE TArray<FTeam> GetTeams() const { return m_Teams; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const override;
	//virtual void BeginPlay() override;

private:
};
