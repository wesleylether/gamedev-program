// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "SineWaveRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ASineWaveRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	FRotator MaxAngles = FRotator(180.0f, 90.0f, 45.0f);

	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	FRotator RotationSpeeds = FRotator(100.0f, 75.0f, 50.0f);

	FRotator InitialRotation;
	float RunningTime = 0.0f;
};