// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"


// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBottom"));
	RootComponent = ChestBottom;

	ChestLid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestLid"));
	ChestLid->SetupAttachment(ChestBottom);

	TargetPitch = 110.0f;

	bIsOpen = false;

}

void ASItemChest::Interact_Implementation(AActor* InstigatorPawn)
{
	if (bIsOpen) {
		ChestLid->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		bIsOpen = false;
	}
	else {
		ChestLid->SetRelativeRotation(FRotator(TargetPitch, 0.0f, 0.0f));
		bIsOpen = true;
	}
}

