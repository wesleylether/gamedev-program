#include "BasicMovement.h"

ABasicMovement::ABasicMovement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasicMovement::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	FVector NewLocation = CurrentLocation + FVector(0.0f, 0.0f, MovementSpeed * DeltaTime);

	SetActorLocation(NewLocation);
}
