// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{

	Health = 100.0f;

	HealthMax = 100.0f;
} 


float USAttributeComponent::GetCurrentHealth()
{
	return Health;
}

float USAttributeComponent::GetMaxHealth()
{
	return HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	Health += Delta;

	Health = FMath::Clamp(Health, 0.0f, HealthMax);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	return true;
}
