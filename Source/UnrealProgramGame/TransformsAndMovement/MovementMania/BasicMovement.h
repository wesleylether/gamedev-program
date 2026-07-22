// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TransformsAndMovement/Base/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "BasicMovement.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABasicMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ABasicMovement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};