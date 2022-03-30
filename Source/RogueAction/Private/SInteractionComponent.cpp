// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Private/KismetTraceUtils.h"
#include "SGameplayInterface.h"


static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("ra.DebugDrawInteraction"), true, TEXT("Toggle Debug Lines for Interact Component."), ECVF_Cheat);


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceDistance = 1000.0f;

	// ...
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);  // Set the objects to query against

	AActor* MyOwner = GetOwner();  // Our Character

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	//FHitResult HitResult;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, ObjectQueryParams);

	// Line trace by shape
	float HitRadius = 30.0f;
	/*TArray<FHitResult> HitResults;*/
	FHitResult HitResult;
	FCollisionShape Shape;
	Shape.SetSphere(HitRadius);
	/*bool bBlockingHits = GetWorld()->SweepMultiByObjectType(HitResults, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);*/
	bool bBlockingHits = GetWorld()->SweepSingleByObjectType(HitResult, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHits ? FColor::Green : FColor::Red;



	/*for (FHitResult Hit : HitResults) {
		AActor* HitActor = Hit.GetActor();

		if (HitActor) {
			if (HitActor->Implements<USGameplayInterface>()) {

				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}

		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, HitRadius, 32, LineColor, false, 2.0f);

		

		
	}*/
	AActor* HitActor = HitResult.GetActor();

	if (HitActor) {
		if (HitActor->Implements<USGameplayInterface>()) {

			APawn* MyPawn = Cast<APawn>(MyOwner);
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

	if (bDebugDraw) {
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, HitRadius, 32, LineColor, false, 2.0f);
		/*DrawDebugSphere(GetWorld(), Hit.ImpactPoint, HitRadius, 32, LineColor, false, 2.0f);*/
	}
	
	
	if (bDebugDraw) {
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	}
	




	/*AActor* HitActor = HitResult.GetActor();

	if (HitActor) {
		if (HitActor->Implements<USGameplayInterface>()) {

			APawn* MyPawn = Cast<APawn>(MyOwner);
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);*/


}