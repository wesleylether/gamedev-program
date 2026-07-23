#include "PingPongRotation.h"

void APingPongRotation::BeginPlay()
{
	Super::BeginPlay();

	RotationLeft = RotationAmount;

	RotationDirection = 1;
}

void APingPongRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float YawRotation = RotationSpeed * DeltaTime;

	RotationLeft -= YawRotation;

	if (RotationLeft > 0.0f)
	{
		const FRotator ToRotate = FRotator(0.0f, YawRotation * RotationDirection, 0.0f);
		AddActorLocalRotation(ToRotate);
	}
	else
	{
		RotationLeft = RotationAmount;
		RotationDirection *= -1;
	}
}
