// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PALHU_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Damage(int Damage);
	UFUNCTION(BlueprintCallable)
	void ResetCurrentLife();

	FORCEINLINE bool IsAlive() const { return bIsAlive; }
	FORCEINLINE int GetMaxHealth() const { return MaxHealPoints; }
	FORCEINLINE int GetCurrentHealth() const { return CurrentHealPoints; }

protected:
	UPROPERTY(Category = Health, EditAnywhere, BlueprintReadWrite)
	int MaxHealPoints;
	UPROPERTY(Category = Health, BlueprintReadOnly)
	int CurrentHealPoints;
	UPROPERTY(Category = Health, BlueprintReadOnly)
	bool bIsAlive;
};
