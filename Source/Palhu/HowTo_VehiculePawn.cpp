// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HowTo_VehiculePawn.h"
#include "HowTo_VehiculeWheelFront.h"
#include "HowTo_VehiculeWheelRear.h"
#include "HowTo_VehiculeHud.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMesh.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

AHowTo_VehiculePawn::AHowTo_VehiculePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	bInReverseGear = false;
	JumpMultiplier = 1000.0f;

	WeaponsBase = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponsBase"));
	WeaponsBase->SetupAttachment(GetMesh());
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(WeaponsBase);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponsManager"));
	AddOwnedComponent(WeaponComponent);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	AddOwnedComponent(HealthComponent);
}

void AHowTo_VehiculePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHowTo_VehiculePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHowTo_VehiculePawn::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AHowTo_VehiculePawn::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AHowTo_VehiculePawn::YawCamera);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AHowTo_VehiculePawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AHowTo_VehiculePawn::OnHandbrakeReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHowTo_VehiculePawn::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHowTo_VehiculePawn::Jump);
}

void AHowTo_VehiculePawn::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AHowTo_VehiculePawn::Fire()
{
	if (WeaponComponent && WeaponMesh)
		WeaponComponent->SpawnProjectile(WeaponMesh->GetComponentTransform(), this);
}

void AHowTo_VehiculePawn::Jump()
{
	USkeletalMeshComponent* RootMesh = GetMesh();

	if (RootMesh && RootMesh->IsSimulatingPhysics() && WheelsAreGrounded())
	{
		
		RootMesh->AddImpulse(FVector::UpVector * JumpMultiplier);
	}
}

void AHowTo_VehiculePawn::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AHowTo_VehiculePawn::PitchCamera(float val)
{
	m_CameraInput.Y = val;
}

void AHowTo_VehiculePawn::YawCamera(float val)
{
	m_CameraInput.X = val;
}

void AHowTo_VehiculePawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AHowTo_VehiculePawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

int AHowTo_VehiculePawn::GetMaxHealth() const
{
	if (HealthComponent == nullptr)
		return 0;
	return HealthComponent->GetMaxHealth();
}

int AHowTo_VehiculePawn::GetCurrentHealth() const
{
	if (HealthComponent == nullptr)
		return 0;
	return HealthComponent->GetCurrentHealth();
}

float AHowTo_VehiculePawn::GetCurrentSpeed() const
{
	return 0.0f;
}

int AHowTo_VehiculePawn::GetCurrentGear() const
{
	return GetVehicleMovement()->GetCurrentGear();
}

void AHowTo_VehiculePawn::Tick(float Delta)
{
	Super::Tick(Delta);

	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;
	RotateSpringArm();
	RotateWeapons();
	if (HealthComponent->IsAlive() == false)
	{
		Destroy(this);
	}	
}

void AHowTo_VehiculePawn::BeginPlay()
{
	Super::BeginPlay();

}

void AHowTo_VehiculePawn::RotateSpringArm()
{
	if (SpringArm == nullptr)
		return;
	FRotator NewRotation = SpringArm->GetComponentRotation();
	NewRotation.Yaw += m_CameraInput.X;
	NewRotation.Pitch += m_CameraInput.Y;
	SpringArm->SetWorldRotation(NewRotation);
}

void AHowTo_VehiculePawn::RotateWeapons()
{
	FVector WeaponTargetPosition;
	FRotator NewWeaponRotation;

	if (Camera == nullptr || WeaponMesh == nullptr)
		return;
	WeaponTargetPosition = Camera->GetForwardVector() * 10000.f + Camera->GetComponentLocation();
	NewWeaponRotation = UKismetMathLibrary::FindLookAtRotation(WeaponMesh->GetComponentLocation(), WeaponTargetPosition);
	WeaponMesh->SetWorldRotation(NewWeaponRotation);
}

bool AHowTo_VehiculePawn::WheelsAreGrounded()
{
	UWheeledVehicleMovementComponent* WheelComponent = GetVehicleMovement();

	if (WheelComponent == nullptr)
		return false;
	for (size_t i = 0; i < WheelComponent->Wheels.Num(); i++)
	{
		if (WheelComponent->Wheels[i]->IsInAir())
			return false;
	}
	return true;
}

#undef LOCTEXT_NAMESPACE
