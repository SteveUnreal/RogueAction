// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "SMagicProjectile.generated.h"

class UAudioComponent;
class USoundCue;
class UParticleSystem;

UCLASS()
class ROGUEACTION_API ASMagicProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:

	ASMagicProjectile();

protected:
	
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* AudioComp;

	//UPROPERTY(EditDefaultsOnly)
	//USoundBase* FlightSound;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* FlightSoundCue;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ImpactSoundCue;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionEmitter;

	UPROPERTY(EditDefaultsOnly)
	float TimeToLive;

	FTimerHandle TimeToLiveHandle;

	//UPROPERTY(EditDefaultsOnly)
	//USoundBase* ImpactSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DestroyProjectile();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};