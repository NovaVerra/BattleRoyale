// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BattleRoyaleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BattleRoyaleCharacter.h"
#include "BattleRoyaleGameMode.h"

ABattleRoyaleProjectile::ABattleRoyaleProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABattleRoyaleProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ABattleRoyaleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		if (ABattleRoyaleCharacter* HitPlayer = Cast<ABattleRoyaleCharacter>(OtherActor)) // if we hit someone with bullet
		{
			if (ABattleRoyaleGameMode* GM = Cast<ABattleRoyaleGameMode>(GetWorld()->GetAuthGameMode())) // if we have, grab their game mode
			{
				ABattleRoyaleCharacter* Killer = Cast<ABattleRoyaleCharacter>(GetOwner()); // tell game mode someone has died
				GM->PlayerDied(HitPlayer, Killer);

				HitPlayer->Killer = Killer;
				HitPlayer->OnRep_Killer();
			}
		}
	}
}