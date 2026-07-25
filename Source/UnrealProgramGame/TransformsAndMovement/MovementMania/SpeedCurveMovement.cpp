#include "SpeedCurveMovement.h"

void ASpeedCurveMovement::BeginPlay()
{
	Super::BeginPlay();

	if (!SpeedCurve)
		return;

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(0, 0, 300.0f);

	Destination = EndLocation;

	InterpolationSpeed = MovementSpeed;
	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	SpeedCurve->GetTimeRange(MinTime, MaxTime);

	CurveLength = MaxTime - MinTime;
}

void ASpeedCurveMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpeedCurve)
		return;

	double Time = GetWorld()->GetTimeSeconds();
	Time = FMath::Fmod(Time, CurveLength);

	InterpolationSpeed = SpeedCurve->GetFloatValue(Time);

	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Destination, DeltaTime, InterpolationSpeed);

	if (NewLocation.Equals(Destination))
	{
		if (Destination.Equals(StartLocation))
		{
			Destination = EndLocation;
		}
		else if (Destination.Equals(EndLocation))
		{
			Destination = StartLocation;
		}
	}
	SetActorLocation(NewLocation);
}
