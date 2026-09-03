// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomizeScale.h"
#include "Math/UnrealMathUtility.h"

void ARandomizeScale::BeginPlay()
{
	Super::BeginPlay();

	SetRandomScale();
	GetWorldTimerManager().SetTimer(RandomScaleTimerHandle, this, &ARandomizeScale::SetRandomScale, 1.0f, true);
}

void ARandomizeScale::SetRandomScale()
{
	const float RandomXScale = FMath::RandRange(0.5f, 3.0f);
	const float RandomYScale = FMath::RandRange(0.5f, 3.0f);
	const float RandomZScale = FMath::RandRange(0.5f, 3.0f);
	ScaleRange = FVector(RandomXScale, RandomYScale, RandomZScale);
	SetActorScale3D(ScaleRange);
}
