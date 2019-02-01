// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehicleWheel.h"

#include "HowTo_VehiculePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UWeaponComponent;
class UHealthComponent;

UCLASS(config=Game)
class AHowTo_VehiculePawn : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponsBase;
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY(Category = Health, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	
	AHowTo_VehiculePawn();

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
	float JumpMultiplier;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float Delta) override;
protected:
	virtual void BeginPlay() override;

public:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void PitchCamera(float val);
	void YawCamera(float val);
	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void Jump();
	void Jump_Implementation();
	bool Jump_Validate();

	void OnHandbrakePressed();
	void OnHandbrakeReleased();

	int GetMaxHealth() const;
	int GetCurrentHealth() const;
	float GetCurrentSpeed() const;
	int GetCurrentGear() const;

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE UHealthComponent* GetHealth() const { return HealthComponent; }

private:
	void RotateSpringArm();
	void RotateWeapons();
	bool WheelsAreGrounded();

	FVector2D m_CameraInput;
};
