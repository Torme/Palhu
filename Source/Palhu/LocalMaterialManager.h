// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalMaterialManager.generated.h"

UCLASS()
class PALHU_API ALocalMaterialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocalMaterialManager();

	void UpdatePlayersMaterials();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
