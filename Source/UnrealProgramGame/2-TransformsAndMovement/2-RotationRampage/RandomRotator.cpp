#include "RandomRotator.h"

void ARandomRotator::BeginPlay()
{
	Super::BeginPlay();

	switch (FMath::RandRange(0, 2))
	{
		default:
		case 0:
			Rotation.Pitch = MovementSpeed;
			break;
		case 1:
			Rotation.Yaw = MovementSpeed;
			break;
		case 2:
			Rotation.Roll = MovementSpeed;
			break;
	}
}

void ARandomRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(Rotation * DeltaTime);
}
