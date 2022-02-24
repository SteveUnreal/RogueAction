// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealingValue = 40.0f;

}

void ASHealthPotion::Interact_Implementation(AActor* InstigatorPawn)
{
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp) {

		if (AttributeComp->GetCurrentHealth() != AttributeComp->GetMaxHealth()) {
			Super::Interact_Implementation(InstigatorPawn);
			AttributeComp->ApplyHealthChange(InstigatorPawn, HealingValue);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Ignoring actor because health is full."));
		}
		
	}

}
