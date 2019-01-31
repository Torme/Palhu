// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "HowTo_VehiculePawn.h"
#include "HealthComponent.h"
#include "Engine/Engine.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	//CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection_Implementation(const FVector & ShootDirection)
{
	
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("HIT"));
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Hit sois meme"));
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent * HOverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & Hit)
{
	AHowTo_VehiculePawn* OverlapedPawn;

	if (OtherActor && OtherActor != GetOwner())
	{
		OverlapedPawn = Cast<AHowTo_VehiculePawn>(OtherActor);
		if (OverlapedPawn)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("OVERLAPPED a vehicle"));
			OverlapedPawn->GetHealth()->Damage(1);
			Destroy(this);
		}
	}
}

