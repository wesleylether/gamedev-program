#include "UniformScale.h"

AUniformScale::AUniformScale()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUniformScale::BeginPlay()
{
	Super::BeginPlay();
}

void AUniformScale::Tick(float DeltaTime)
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

void AUniformScale::ManualScale(float DeltaTime)
{
	const FVector CurrentScale = GetActorScale3D();
	const FVector TargetScale = FVector(MaxScale);

	if (CurrentScale.Size() < TargetScale.Size())
	{
		FVector NewScale = CurrentScale + FVector(ScaleSpeed * DeltaTime);

		if (NewScale.Size() > TargetScale.Size())
		{
			NewScale = TargetScale;
		}

		SetActorScale3D(NewScale);
	}
}

void AUniformScale::InterpolationScale(float DeltaTime)
{
	const FVector NewScale = FMath::VInterpConstantTo(GetActorScale3D(), FVector(MaxScale), DeltaTime, ScaleSpeed);
	SetActorScale3D(NewScale);
}
