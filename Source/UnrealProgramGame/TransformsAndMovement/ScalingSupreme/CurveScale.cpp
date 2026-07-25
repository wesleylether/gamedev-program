
#include "CurveScale.h"

void ACurveScale::BeginPlay()
{
	Super::BeginPlay();

	if (!CurveScale)
		return;

	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	CurveScale->GetTimeRange(MinTime, MaxTime);
	CurveLength = MaxTime - MinTime;
	BaseScale = GetActorScale3D();
	TargetScale = FVector(MaxScale);
}

void ACurveScale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurveScale)
		return;

	double Time = GetWorld()->GetTimeSeconds();
	Time = FMath::Fmod(Time, CurveLength);

	const FVector CurrentScale = GetActorScale3D();
	const float	  ScaleSpeed = CurveScale->GetFloatValue(Time);
	const FVector NewScale = FMath::VInterpConstantTo(CurrentScale, TargetScale, DeltaTime, ScaleSpeed);

	if (NewScale.Equals(TargetScale))
	{
		if (TargetScale.Equals(FVector(MaxScale)))
		{

			TargetScale = BaseScale;
		}
		else if (TargetScale.Equals(BaseScale))
		{
			TargetScale = FVector(MaxScale);
		}
	}

	SetActorScale3D(NewScale);
}
