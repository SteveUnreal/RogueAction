// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPickupItem.generated.h"

class UBoxComponent;

UCLASS()
class ROGUEACTION_API ASPickupItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ASPickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimeoutHandle;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	float TimeoutDelay;

	virtual void Interact_Implementation(AActor* InstigatorPawn) override;

	void HideItem();
	void ShowItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
