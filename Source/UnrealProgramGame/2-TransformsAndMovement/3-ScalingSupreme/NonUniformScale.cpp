#include "NonUniformScale.h"

void ANonUniformScale::BeginPlay()
{
	Super::BeginPlay();

	SetRandomValues();
	GetWorldTimerManager().SetTimer(RandomScaleTimerHandle, this, &ANonUniformScale::SetRandomValues, 5.0f, true);
}

void ANonUniformScale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterpolation)
	{
		InterpolationScale(DeltaTime);
	}
	else
	{
		ManualScale(DeltaTime);
	}
}

void ANonUniformScale::ManualScale(float DeltaTime)
{
	const FVector CurrentScale = GetActorScale3D();

	FVector NewScale = CurrentScale + ScaleSpeed * DeltaTime;
	NewScale.X = FMath::Min(NewScale.X, MaxScale.X);
	NewScale.Y = FMath::Min(NewScale.Y, MaxScale.Y);
	NewScale.Z = FMath::Min(NewScale.Z, MaxScale.Z);

	SetActorScale3D(NewScale);
}

void ANonUniformScale::InterpolationScale(float DeltaTime)
{
	const FVector CurrentScale = GetActorScale3D();

	const FVector NewScale(
		FMath::FInterpConstantTo(CurrentScale.X, MaxScale.X, DeltaTime, ScaleSpeed.X),
		FMath::FInterpConstantTo(CurrentScale.Y, MaxScale.Y, DeltaTime, ScaleSpeed.Y),
		FMath::FInterpConstantTo(CurrentScale.Z, MaxScale.Z, DeltaTime, ScaleSpeed.Z));

	SetActorScale3D(NewScale);
}

void ANonUniformScale::SetRandomValues()
{
	MaxScale = FVector(
		FMath::FRand() * 2.5f + 0.5f,
		FMath::FRand() * 2.5f + 0.5f,
		FMath::FRand() * 2.5f + 0.5f);

	ScaleSpeed = FVector(
		FMath::FRand() * 2.0f + 1.0f,
		FMath::FRand() * 2.0f + 1.0f,
		FMath::FRand() * 2.0f + 1.0f);
}
