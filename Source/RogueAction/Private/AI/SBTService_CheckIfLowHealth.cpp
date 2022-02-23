// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "AI/SAIController.h"
#include "AI/SBTService_CheckIfLowHealth.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"


void USBTService_CheckIfLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	// Check distance between AI pawn and target actor

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackBoardComp)) {
		bool bHealthIsLow = BlackBoardComp->GetValueAsBool("bHealthIsLow");
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController)) {
			APawn* MyPawn = MyController->GetPawn();
			if (ensure(MyPawn)) {
				UE_LOG(LogTemp, Log, TEXT("MyCharacter is valid."));
				USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
				if (AttributeComp) {
					float CurrentHealth = AttributeComp->GetCurrentHealth();
					if (CurrentHealth <= (AttributeComp->GetMaxHealth() / 4.0f)) {
						BlackBoardComp->SetValueAsBool(HealthLowKey.SelectedKeyName, true);
					}
					else {
						BlackBoardComp->SetValueAsBool(HealthLowKey.SelectedKeyName, false);
					}
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("AttributeComp is null."));

				}
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("MyCharacter is null."));
			}
			
			
		}
	}
}
