// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupItem.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"


// Sets default values
ASPickupItem::ASPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	BoxComp->SetupAttachment(RootComponent);

	TimeoutDelay = 10.0f;

}

void ASPickupItem::Interact_Implementation(AActor* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("%S interacting with %s"), *GetNameSafe(InstigatorPawn), *GetNameSafe(this));
	HideItem();
	GetWorldTimerManager().SetTimer(TimeoutHandle, this, &ASPickupItem::ShowItem, TimeoutDelay);

}

// Called when the game starts or when spawned
void ASPickupItem::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ASPickupItem::HideItem()
{
	UE_LOG(LogTemp, Log, TEXT("SHould hide"));
	MeshComp->ToggleVisibility(false);
	this->SetHidden(true);
}

void ASPickupItem::ShowItem()
{
	UE_LOG(LogTemp, Log, TEXT("SHould show"));
	MeshComp->ToggleVisibility(true);
	this->SetHidden(false);
}

// Called every frame
void ASPickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

