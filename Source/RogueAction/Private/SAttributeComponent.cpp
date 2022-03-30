// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("ra.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for attribute component."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{

	Health = 100.0f;

	HealthMax = 100.0f;
} 

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor) {
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}


bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	if (Actor) {
		USAttributeComponent* AttributeComp = GetAttributes(Actor);
		if (AttributeComp) {
			return AttributeComp->IsAlive();
		}
	}

	return false;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	ApplyHealthChange(InstigatorActor, -GetMaxHealth());

	if (this->GetCurrentHealth() <= 0.0f) {
		return true;
	}
	return false;
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

	if (!GetOwner()->CanBeDamaged()) {
		return false;
	}

	if (Delta < 0.0f) {
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;

	Health += Delta;

	Health = FMath::Clamp(Health, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	if (ActualDelta < 0.0f && Health == 0.0f) {  // Died
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM) {
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return true;
}
