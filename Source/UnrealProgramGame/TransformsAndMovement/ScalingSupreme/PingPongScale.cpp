#include "PingPongScale.h"

void APingPongScale::BeginPlay()
{
	Super::BeginPlay();

	if (!bUniform)
	{
		MaxScale = FVector(
			FMath::FRand() * 3.0f + 1.5f,
			FMath::FRand() * 3.0f + 1.5f,
			FMath::FRand() * 3.0f + 1.5f);

		ScaleSpeed = FVector(
			FMath::FRand() * 2.0f + 1.0f,
			FMath::FRand() * 2.0f + 1.0f,
			FMath::FRand() * 2.0f + 1.0f);
	}

	BaseScale = GetActorScale3D();
	TargetScale = MaxScale;
}

void APingPongScale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector CurrentScale = GetActorScale3D();
	auto ToggleTargetAxis = [](double AxisValue, double BaseAxis, double MaxAxis, double& TargetAxis)
	{
		if (!FMath::IsNearlyEqual(AxisValue, TargetAxis))
		{
			return;
		}

		TargetAxis = FMath::IsNearlyEqual(TargetAxis, MaxAxis) ? BaseAxis : MaxAxis;
	};

	if (bUniform)
	{
		FVector NewScale = FMath::VInterpConstantTo(CurrentScale, TargetScale, DeltaTime, ScaleSpeed.X);

		if (NewScale.Equals(TargetScale))
		{
			if (TargetScale.Equals(MaxScale))
			{
				TargetScale = BaseScale;
			}
			else if (TargetScale.Equals(BaseScale))
			{
				TargetScale = MaxScale;
			}
		}
		SetActorScale3D(NewScale);
	}
	else
	{
		FVector NewScale(
			FMath::FInterpConstantTo(CurrentScale.X, TargetScale.X, DeltaTime, ScaleSpeed.X),
			FMath::FInterpConstantTo(CurrentScale.Y, TargetScale.Y, DeltaTime, ScaleSpeed.Y),
			FMath::FInterpConstantTo(CurrentScale.Z, TargetScale.Z, DeltaTime, ScaleSpeed.Z));

		ToggleTargetAxis(NewScale.X, BaseScale.X, MaxScale.X, TargetScale.X);
		ToggleTargetAxis(NewScale.Y, BaseScale.Y, MaxScale.Y, TargetScale.Y);
		ToggleTargetAxis(NewScale.Z, BaseScale.Z, MaxScale.Z, TargetScale.Z);

		SetActorScale3D(NewScale);
	}
}
