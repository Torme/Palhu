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
class UMaterial;

UCLASS(config=Game)
class AHowTo_VehiculePawn : public AWheeledVehicle
{
	GENERATED_BODY()

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpringArmMaxPitch;
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpringArmMinPitch;
	
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponsBase;
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY(Category = Health, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_WeaponRotChange, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator WeaponCurrentRotation;
	/*UPROPERTY(Transient, ReplicatedUsing = OnRep_WeaponRotChange, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator WeaponCurrentRotation;
	UPROPERTY(Transient, ReplicatedUsing = OnRep_WeaponRotChange, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator WeaponCurrentRotation;*/

	UFUNCTION()
	void OnRep_WeaponRotChange();
	/*UFUNCTION()
	void OnRep_RootMeshRotChange();
	UFUNCTION()
	void OnRep_RootMeshPosChange();*/

	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float FireCooldown;

	UPROPERTY(Category = Apparence, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<int> MaterialsIndex;
	UPROPERTY(Category = Apparence, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TMap<int, UMaterial*> Materials;
	
public:
	AHowTo_VehiculePawn();

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
	float JumpMultiplier;

	UPROPERTY(Category = Debug, EditAnywhere, BlueprintReadOnly)
		FVector WeaponTargetPos;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Tick(float Delta) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//void SetTeamIndex (int newTeamIndex);
	//int	GetTeamIndex();

protected:
	virtual void BeginPlay() override;

public:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void PitchCamera(float val);
	void YawCamera(float val);
	void ResetCamera();
	void BeginFire();
	void EndFire();
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
	static float SPRING_ARM_DEFAULT_PITCH;
	static float SPRING_ARM_DEFAULT_LENGTH;
	static float CAMERA_RESET_COMPLETE_TIME;

	void RotateSpringArm();
	void RotateWeapons();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRotateWeapons(FRotator NewRotation);
	void ServerRotateWeapons_Implementation(FRotator NewRotation);
	bool ServerRotateWeapons_Validate(FRotator NewRotation);
		
	bool WheelsAreGrounded();
	void ResetSpringArmPosition(float Delta);

	FVector2D m_CameraInput;
	FRotator m_BeginRotation;
	bool m_bIsResetingCamera;
	float m_CurrentCameraResetAlpha;

	bool m_bIsFirePressed;
	
	FTimerHandle m_FireCooldownTimer;
	bool m_bFireCooldownIsOver;

	void StartTimer_ShootCooldown();
	void StopTimer_ShootCooldown();
	void TimerHandle_ShootCooldownIsOver();
};
