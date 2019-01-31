// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PALHU_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = Spawner, Server, Reliable, WithValidation)
	void SpawnProjectile(const FTransform &Transform, AActor* Owner);
	bool SpawnProjectile_Validate(const FTransform &Transform, AActor* Owner);
	void SpawnProjectile_Implementation(const FTransform &Transform, AActor* Owner);

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;
		
};
