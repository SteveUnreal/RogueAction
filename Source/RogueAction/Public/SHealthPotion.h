// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPickupItem.h"
#include "SHealthPotion.generated.h"

UCLASS()
class ROGUEACTION_API ASHealthPotion : public ASPickupItem
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(EditDefaultsOnly)
	float HealingValue;

	virtual void Interact_Implementation(AActor* InstigatorPawn) override;

};
