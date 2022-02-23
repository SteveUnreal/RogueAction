// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


ATeleportProjectile::ATeleportProjectile()
{

	ParticleEmitter = CreateDefaultSubobject<UParticleSystem>(TEXT("ParticleEmitter"));
	

}

void ATeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(Explode_TimeHandle, this, &ATeleportProjectile::Explode, 0.2f);

	GetWorldTimerManager().SetTimer(Teleport_TimeHandle, this, &ATeleportProjectile::Teleport, 0.4f);
}

void ATeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ATeleportProjectile::OnParticleHit);
}

void ATeleportProjectile::Teleport()
{
	if (ensure(!IsPendingKill())) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEmitter, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), true);
		APawn* ProjectileInstigator = GetInstigator();
		ProjectileInstigator->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
		Destroy();
	}
	
}

void ATeleportProjectile::Explode()
{
	MovementComp->Deactivate();
}

void ATeleportProjectile::OnParticleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("%s Component hit %s!!"), *GetNameSafe(HitComponent), *GetNameSafe(OtherActor));
	// We want to stop projectile instantly and explode.
	GetWorldTimerManager().ClearAllTimersForObject(this);
	Teleport();

}
