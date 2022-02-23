// Fill out your copyright notice in the Description page of Project Settings.


#include "AExplosiveBarrel.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAExplosiveBarrel::AAExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//RootComponent = SceneComp;

	//CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	//CapsuleComp->SetupAttachment(RootComponent);
	//RootComponent = CapsuleComp;
	//CapsuleComp->SetupAttachment(SceneComp);
	//CapsuleComp->SetCollisionObjectType(ECC_PhysicsBody);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	//MeshComp->SetupAttachment(CapsuleComp);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	/*EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(CapsuleComp);*/


	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->Radius = DamageRadius;
	RadialForceComp->ImpulseStrength = ImpulseStrength;
	RadialForceComp->bImpulseVelChange = true;  // Takes mass into account
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComp->SetAutoActivate(false);





	

}

// Called when the game starts or when spawned
void AAExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAExplosiveBarrel::PostInitializeComponents() {
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &AAExplosiveBarrel::BeginOverlap);
}

void AAExplosiveBarrel::Explode()
{

	// Play effect
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectComp, this->GetActorLocation());
	

	// Cause radial damage
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("Exploding."));

	// Delete?


}

void AAExplosiveBarrel::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Overalp with %s"), *GetNameSafe(OtherActor));

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
	Explode();
}
