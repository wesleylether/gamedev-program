#include "InterpolatedMovement.h"

AInterpolatedMovement::AInterpolatedMovement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInterpolatedMovement::BeginPlay()
{
	Super::BeginPlay();

	MovementSpeed = 200.0f;
}

void AInterpolatedMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!StartActor || !EndActor)
		return;

	FVector StartLocation = StartActor->GetActorLocation();
	FVector EndLocation = EndActor->GetActorLocation();

	FVector Destination = bMovingToEnd ? EndLocation : StartLocation;

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, Destination, DeltaTime, MovementSpeed);

	SetActorLocation(NewLocation);

	if (NewLocation.Equals(Destination))
		bMovingToEnd = !bMovingToEnd;
}
