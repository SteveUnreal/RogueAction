// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "TeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEACTION_API ATeleportProjectile : public ABaseProjectile
{
	GENERATED_BODY()

protected:
	ATeleportProjectile();

	void Teleport();

	void Explode();

	void BeginPlay();

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ParticleEmitter;

protected:

	FTimerHandle Explode_TimeHandle;
	FTimerHandle Teleport_TimeHandle;

	UFUNCTION()
	void OnParticleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void PostInitializeComponents();
};
