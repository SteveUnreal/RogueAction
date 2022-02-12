// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

	bUseControllerRotationYaw = false;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TraceDistance = 10000.0f;

}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{

	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	AddMovementInput(controlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{

	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	// From UKismetMathLibrary GetRightVector (Found via shift + alt + s on 'rightvector')
	FVector RightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::Jump()
{
	Super::Jump();
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//// To spawn from hand we can select the socket added to a bone or otherwise.
	//FVector HandLocation = GetMesh()->GetSocketLocation(PrimarySocketName);

	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::SecondaryAttack_TimeElapsed, 0.2f);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{

	// Line trace for impact point
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	// Get Screen center
	FVector CameraLocation = CameraComp->GetComponentLocation();
	FRotator CameraRotator = CameraComp->GetComponentRotation();

	FHitResult HitResult;
	FVector End = CameraLocation + (CameraRotator.Vector() * TraceDistance);

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, End, ObjectQueryParams);
	//DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Red, false, 10.0f);

	// To spawn from hand we can select the socket added to a bone or otherwise.
	FVector HandLocation = GetMesh()->GetSocketLocation(PrimarySocketName);
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);


	if (bBlockingHit) {
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Black, false, 2.0f);

		// Get new rotation
		FVector NewVec = HitResult.ImpactPoint - HandLocation;
		SpawnTM = FTransform(NewVec.Rotation(), HandLocation);

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Did not hit anything for aim line trace."));
		FVector LineEndVec = End - HandLocation;
		SpawnTM = FTransform(LineEndVec.Rotation(), HandLocation);

	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, SpawnTM, SpawnParams);
	
	
}

void ASCharacter::SecondaryAttack_TimeElapsed()
{

	// Line trace for impact point
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	// Get Screen center
	FVector CameraLocation = CameraComp->GetComponentLocation();
	FRotator CameraRotator = CameraComp->GetComponentRotation();

	FHitResult HitResult;
	FVector End = CameraLocation + (CameraRotator.Vector() * TraceDistance);

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, End, ObjectQueryParams);
	//DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Red, false, 10.0f);

	// To spawn from hand we can select the socket added to a bone or otherwise.
	FVector HandLocation = GetMesh()->GetSocketLocation(PrimarySocketName);
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);


	if (bBlockingHit) {
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Black, false, 2.0f);

		// Get new rotation
		FVector NewVec = HitResult.ImpactPoint - HandLocation;
		SpawnTM = FTransform(NewVec.Rotation(), HandLocation);

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Did not hit anything."));

	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, SpawnTM, SpawnParams);


}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp) {
		InteractionComp->PrimaryInteract();
	}

}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::Teleport_TimeElapsed, 0.2f);
}

bool ASCharacter::CheckBlockingHitForAttack(FHitResult& HitResult)
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	// Get Screen center
	FVector CameraLocation = CameraComp->GetComponentLocation();
	FRotator CameraRotator = CameraComp->GetComponentRotation();

	FHitResult CheckHitResult;
	FVector End = CameraLocation + (CameraRotator.Vector() * TraceDistance);

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(CheckHitResult, CameraLocation, End, ObjectQueryParams);

	HitResult = CheckHitResult;

	return bBlockingHit;
}

void ASCharacter::Teleport_TimeElapsed()
{
	// Line trace for impact point
	//FCollisionObjectQueryParams ObjectQueryParams;
	//ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	//// Get Screen center
	//FVector CameraLocation = CameraComp->GetComponentLocation();
	//FRotator CameraRotator = CameraComp->GetComponentRotation();

	FHitResult HitResult;
	//FVector End = CameraLocation + (CameraRotator.Vector() * TraceDistance);

	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, End, ObjectQueryParams);
	//DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Red, false, 10.0f);

	bool bBlockingHit = CheckBlockingHitForAttack(HitResult);

	// To spawn from hand we can select the socket added to a bone or otherwise.
	FVector HandLocation = GetMesh()->GetSocketLocation(PrimarySocketName);
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);


	if (bBlockingHit) {
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Black, false, 2.0f);

		// Get new rotation
		FVector NewVec = HitResult.ImpactPoint - HandLocation;
		SpawnTM = FTransform(NewVec.Rotation(), HandLocation);

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Did not hit anything for aim line trace."));

	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(TeleportProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta <= 0.0f && NewHealth != 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("SHOULD FLASH"));
		USkeletalMeshComponent* MeshComp = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Delta < 0.0f) {
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", EInputEvent::IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", EInputEvent::IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Teleport", EInputEvent::IE_Pressed, this, &ASCharacter::Teleport);

}

