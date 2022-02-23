// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "BlackholeProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class ROGUEACTION_API ABlackholeProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	ABlackholeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle Blackhole_TimeHandle;

	void DestroySelf();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URadialForceComponent *ForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "Blackhole")
	float BlackholeStrength;

	void PostInitializeComponents();
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
