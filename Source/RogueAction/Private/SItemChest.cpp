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

}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::Interact_Implementation(AActor* InstigatorPawn)
{
	ChestLid->SetRelativeRotation(FRotator(TargetPitch, 0.0f, 0.0f));
}

