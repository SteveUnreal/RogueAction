// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ROGUEACTION_API ASCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	// Allows assignment through BP
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	FName PrimarySocketName;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
