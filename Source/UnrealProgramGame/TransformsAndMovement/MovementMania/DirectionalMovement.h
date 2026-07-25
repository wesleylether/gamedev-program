// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TransformsAndMovement/Base/BaseMovementActor.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"

#include "DirectionalMovement.generated.h"

class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ADirectionalMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ADirectionalMovement();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

public:
	virtual void Tick(float DeltaTime) override;
};