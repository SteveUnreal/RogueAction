// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "SMagicProjectile.generated.h"


UCLASS()
class ROGUEACTION_API ASMagicProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:

	ASMagicProjectile();

protected:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};