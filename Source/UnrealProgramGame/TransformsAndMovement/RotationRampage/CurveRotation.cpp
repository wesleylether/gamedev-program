#include "CurveRotation.h"

void ACurveRotation::BeginPlay()
{
	Super::BeginPlay();

	if (!CurveFloat)
		return;

	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	CurveFloat->GetTimeRange(MinTime, MaxTime);
	CurveLength = MaxTime - MinTime;
}

void ACurveRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurveFloat)
		return;

	double Time = GetWorld()->GetTimeSeconds();
	Time = FMath::Fmod(Time, CurveLength);

	MovementSpeed = CurveFloat->GetFloatValue(Time);

	AddActorLocalRotation(FRotator(0.0f, MovementSpeed, 0.0f) * DeltaTime);
}
