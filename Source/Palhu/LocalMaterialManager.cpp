// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalMaterialManager.h"

#include "PrintDebug.h"

// Sets default values
ALocalMaterialManager::ALocalMaterialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALocalMaterialManager::UpdatePlayersMaterials()
{
}

// Called when the game starts or when spawned
void ALocalMaterialManager::BeginPlay()
{
	Super::BeginPlay();
	
	printf("I;m on the local color manager");
}
