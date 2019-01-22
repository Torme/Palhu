// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AProjectile * UWeaponComponent::SpawnProjectile(FVector Location, FRotator Rotation, AActor * Owner)
{
	if (!ProjectileClass || !Owner)
		return nullptr;

	FVector MuzzleLocation = Location + FTransform(Owner->GetActorRotation()).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = Rotation;

	//MuzzleRotation.Pitch += 10.0f;
	UWorld * World = GetWorld();
	if (!World)
		return nullptr;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Owner;
	SpawnParameters.Instigator = Owner->Instigator;
	AProjectile* newProjectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParameters);
	if (!newProjectile)
		return nullptr;
	newProjectile->FireInDirection(FVector());
	return newProjectile;
}

