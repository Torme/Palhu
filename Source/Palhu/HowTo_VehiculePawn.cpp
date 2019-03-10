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
#include "Engine/Public/TimerManager.h"
#include "UnrealNetwork.h"

#include "PrintDebug.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

float AHowTo_VehiculePawn::SPRING_ARM_DEFAULT_PITCH = -5.f;
float AHowTo_VehiculePawn::SPRING_ARM_DEFAULT_LENGTH = 600.f;
float AHowTo_VehiculePawn::CAMERA_RESET_COMPLETE_TIME = 0.5f;

void AHowTo_VehiculePawn::OnRep_WeaponRotChange()
{
	FRotator NewRotation = FRotator::ZeroRotator;
	
	if (WeaponMesh == nullptr)
		return;
	NewRotation.Yaw = WeaponCurrentRotation.Yaw;
	NewRotation.Roll = GetActorRotation().Roll;
	WeaponMesh->SetWorldRotation(NewRotation);
}

AHowTo_VehiculePawn::AHowTo_VehiculePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(SPRING_ARM_DEFAULT_PITCH, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SPRING_ARM_DEFAULT_LENGTH;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	SpringArmMaxPitch = 30.f;
	SpringArmMinPitch = -30.f;

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

	m_TeamIndex = 42;
	m_bIsResetingCamera = false;
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHowTo_VehiculePawn::Fire);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHowTo_VehiculePawn::Jump);
	PlayerInputComponent->BindAction("ResetCamera", IE_Pressed, this, &AHowTo_VehiculePawn::ResetCamera);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AHowTo_VehiculePawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AHowTo_VehiculePawn::OnHandbrakeReleased);
}

void AHowTo_VehiculePawn::Tick(float Delta)
{
	Super::Tick(Delta);

	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;
	if (IsLocallyControlled())
	{
		if (m_bIsResetingCamera)
			ResetSpringArmPosition(Delta);
		else
			RotateSpringArm();
		RotateWeapons();
	}
	if (HealthComponent->IsAlive() == false)
	{
		Destroy(this);
	}
}

void AHowTo_VehiculePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHowTo_VehiculePawn, WeaponCurrentRotation);
}

void AHowTo_VehiculePawn::BeginPlay()
{
	Super::BeginPlay();

}

void AHowTo_VehiculePawn::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AHowTo_VehiculePawn::Fire()
{
	FTransform RelativTransform;

	RelativTransform = WeaponMesh->GetComponentTransform();
	RelativTransform.SetRotation(WeaponCurrentRotation.Quaternion());
	if (WeaponComponent && WeaponMesh)
		WeaponComponent->SpawnProjectile(RelativTransform, this);
}

//void AHowTo_VehiculePawn::Jump_Implementation()
//{
//	USkeletalMeshComponent* RootMesh = GetMesh();
//
//	if (RootMesh && RootMesh->IsSimulatingPhysics() && WheelsAreGrounded())
//	{
//		
//		RootMesh->AddImpulse(FVector::UpVector * JumpMultiplier);
//	}
//}
//
//bool AHowTo_VehiculePawn::Jump_Validate()
//{
//	return true;
//}

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

void AHowTo_VehiculePawn::ResetCamera()
{
	if (SpringArm == nullptr)
		return;
	m_BeginRotation = SpringArm->GetComponentRotation();
	m_bIsResetingCamera = true;
	m_CurrentCameraResetAlpha = 0.f;
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
	if (GetVehicleMovementComponent() == nullptr)
		return 0.0f;
	return GetVehicleMovementComponent()->GetForwardSpeed() * 0.036f;
}

int AHowTo_VehiculePawn::GetCurrentGear() const
{
	return GetVehicleMovement()->GetCurrentGear();
}

void AHowTo_VehiculePawn::SetTeamIndex(int newTeamIndex)
{
	m_TeamIndex = newTeamIndex;
}

int AHowTo_VehiculePawn::GetTeamIndex()
{
	//printf("Get team: %d", m_TeamIndex);
	return m_TeamIndex;
}

void AHowTo_VehiculePawn::RotateSpringArm()
{
	FRotator NewRotation;

	if (SpringArm == nullptr)
		return;
	NewRotation = SpringArm->GetComponentRotation();
	NewRotation.Yaw += m_CameraInput.X;
	NewRotation.Pitch += m_CameraInput.Y;
	NewRotation.Roll = 0;
	if (NewRotation.Pitch > SpringArmMaxPitch)
		NewRotation.Pitch = SpringArmMaxPitch;
	else if (NewRotation.Pitch < SpringArmMinPitch)
		NewRotation.Pitch = SpringArmMinPitch;
	SpringArm->SetWorldRotation(NewRotation);
}

void AHowTo_VehiculePawn::RotateWeapons()
{
	FHitResult CameraForwardingHit;
	FVector WeaponTargetPosition;
	FRotator NewWeaponRotation;
	FVector BulletPos;

	if (Camera == nullptr || WeaponMesh == nullptr)
		return;
	WeaponTargetPosition = Camera->GetForwardVector() * 10000.f + Camera->GetComponentLocation();
	if (GetWorld() && GetWorld()->LineTraceSingleByChannel(CameraForwardingHit, Camera->GetComponentLocation(), WeaponTargetPosition, ECollisionChannel::ECC_WorldDynamic))
	{
		WeaponTargetPosition = CameraForwardingHit.Location;
	}
	BulletPos = WeaponMesh->GetComponentLocation() + FTransform(WeaponCurrentRotation).TransformVector(WeaponComponent->MuzzleOffset);
	NewWeaponRotation = UKismetMathLibrary::FindLookAtRotation(BulletPos, WeaponTargetPosition);
	WeaponTargetPos = WeaponTargetPosition;
	if (IsLocallyControlled())
		ServerRotateWeapons(NewWeaponRotation);
}

void AHowTo_VehiculePawn::ServerRotateWeapons_Implementation(FRotator NewRotation)
{
	FRotator CalculatedRotation;

	CalculatedRotation.Yaw = NewRotation.Yaw;
	CalculatedRotation.Roll = GetActorRotation().Roll;
	WeaponMesh->SetWorldRotation(CalculatedRotation);
	WeaponCurrentRotation = NewRotation;
}

bool AHowTo_VehiculePawn::ServerRotateWeapons_Validate(FRotator NewRotation)
{
	return true;
}

bool AHowTo_VehiculePawn::WheelsAreGrounded()
{
	UWheeledVehicleMovementComponent* WheelComponent = GetVehicleMovement();
	
	if (WheelComponent == nullptr)
		return false;
	for (size_t i = 0; i < WheelComponent->Wheels.Num(); i++)
	{
		if (WheelComponent->Wheels[i]->IsInAir() == false)
			return true;
	}
	return false;
}

void AHowTo_VehiculePawn::ResetSpringArmPosition(float Delta)
{
	FRotator TargetRotation;

	m_CurrentCameraResetAlpha += CAMERA_RESET_COMPLETE_TIME == 0 ? 1 : Delta / CAMERA_RESET_COMPLETE_TIME;
	if (m_CurrentCameraResetAlpha >= 1.f)
		m_CurrentCameraResetAlpha = 1.f;
	TargetRotation = GetActorRotation();
	TargetRotation.Pitch -= SPRING_ARM_DEFAULT_PITCH;
	SpringArm->SetWorldRotation(FMath::Lerp(m_BeginRotation, TargetRotation, m_CurrentCameraResetAlpha));
	if (m_CurrentCameraResetAlpha >= 1.f)
		m_bIsResetingCamera = false;
}

#undef LOCTEXT_NAMESPACE
