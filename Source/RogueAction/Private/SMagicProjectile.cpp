// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


ASMagicProjectile::ASMagicProjectile()
{
	//// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp->SetCollisionProfileName("Projectile");
	//RootComponent = SphereComp;

	//EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//EffectComp->SetupAttachment(SphereComp);

	//MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	//MovementComp->InitialSpeed = 1000.0f;
	//MovementComp->bRotationFollowsVelocity = true;
	//MovementComp->bInitialVelocityInLocalSpace = true;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnProjectileHit);
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
	
	TimeToLive = 1.0f;
	DamageAmount = 20.0f;


}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeToLiveHandle, this, &ASMagicProjectile::DestroyProjectile, TimeToLive);
	// Play the flight sound
	AudioComp->SetSound(FlightSoundCue);
	AudioComp->Play(0.0f);

}



void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (OtherActor != GetInstigator()) {
		if (ensure(!IsPendingKill())) {
			if (OtherActor && OtherActor != GetInstigator()) {
				USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
				if (AttributeComp) {
					AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSoundCue, OtherActor->GetActorLocation());
					DestroyProjectile();
				}
			}
		}
	}
	
	
}

void ASMagicProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetInstigator()) {
		UE_LOG(LogTemp, Log, TEXT("% hit other actor %s"), *GetNameSafe(HitComponent->GetOwner()), *GetNameSafe(OtherActor));
		if (ImpactSoundCue) {
			// Play the hit sound at location
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSoundCue, OtherActor->GetActorLocation());
			DestroyProjectile();

		}
	}
	
}

void ASMagicProjectile::DestroyProjectile()
{
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitter, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), true);
	Destroy();
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
