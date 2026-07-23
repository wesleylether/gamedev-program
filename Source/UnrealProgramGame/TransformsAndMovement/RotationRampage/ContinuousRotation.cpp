#include "ContinuousRotation.h"

void AContinuousRotation::BeginPlay()
{
	Super::BeginPlay();
}

void AContinuousRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, MovementSpeed * DeltaTime, 0.0f));
}
