#include "MultiAxesRotation.h"

void AMultiAxesRotation::BeginPlay()
{
	Super::BeginPlay();
}

void AMultiAxesRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(PitchSpeed * DeltaTime, YawSpeed * DeltaTime, RollSpeed * DeltaTime));
}
