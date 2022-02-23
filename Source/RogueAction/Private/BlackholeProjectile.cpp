// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

ABlackholeProjectile::ABlackholeProjectile()
{
	BlackholeStrength = -100000.0f;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(RootComponent);
	ForceComp->ForceStrength = BlackholeStrength;
	ForceComp->bImpulseVelChange = true;
	ForceComp->bIgnoreOwningActor = true;

}

void ABlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	//this->Destroy()
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(Blackhole_TimeHandle, this,	&ABlackholeProjectile::DestroySelf, 5.0f);
}


void ABlackholeProjectile::PostInitializeComponents() {
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackholeProjectile::ComponentBeginOverlap);
}

void ABlackholeProjectile::DestroySelf()
{
	if (ensure(!IsPendingKill())) {
		Destroy();
	}
	
}


void ABlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForceComp->Activate();
}

void ABlackholeProjectile::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	UE_LOG(LogTemp, Log, TEXT("Blackhole overlap"));

	if (HitComponent->IsSimulatingPhysics()) {
		UE_LOG(LogTemp, Log, TEXT("Is simulating physics"));
		OtherActor->Destroy();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Is not simulating physics"));
	}

}

void ABlackholeProjectile::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Blackhole component overlap"));

	if (OtherComp->IsSimulatingPhysics()) {
		UE_LOG(LogTemp, Log, TEXT("Is simulating physics"));
		OtherActor->Destroy();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Is not simulating physics"));
	}
}
