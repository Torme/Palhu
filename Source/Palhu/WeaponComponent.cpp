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

bool UWeaponComponent::SpawnProjectile_Validate(const FTransform & Transform, AActor * Owner)
{
	return true;
}

void UWeaponComponent::SpawnProjectile_Implementation(const FTransform& Transform, AActor * Owner)
{
	if (!ProjectileClass || !Owner)
		return;

	FVector MuzzleLocation = Transform.GetLocation() + FTransform(Transform.GetRotation()).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = Transform.GetRotation().Rotator();

	UWorld * World = GetWorld();
	if (!World)
		return;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Owner;
	SpawnParameters.Instigator = Owner->Instigator;
	AProjectile* newProjectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParameters);
	if (!newProjectile)
		return;
	newProjectile->FireInDirection(FVector());
}

