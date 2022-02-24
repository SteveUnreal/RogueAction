// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ROGUEACTION_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(AActor* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ASItemChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;


protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestBottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestLid;

	UPROPERTY(BlueprintReadOnly)
	bool bIsOpen;


};
