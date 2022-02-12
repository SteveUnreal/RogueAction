// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AExplosiveBarrel.generated.h"

class UCapsuleComponent;
class URadialForceComponent;

UCLASS()
class ROGUEACTION_API AAExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAExplosiveBarrel();

	virtual void PostInitializeComponents() override;


protected:

	//USceneComponent* SceneComp;

	//UPROPERTY(EditDefaultsOnly)
	//UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	UParticleSystem* EffectComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	

	UPROPERTY(EditAnywhere)
	float ImpulseStrength = 100.0f;

	UPROPERTY(EditAnywhere)
	float DamageRadius = 1000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	


};
