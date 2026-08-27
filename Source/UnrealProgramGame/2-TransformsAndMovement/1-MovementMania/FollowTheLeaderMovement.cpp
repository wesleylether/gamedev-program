#include "FollowTheLeaderMovement.h"

void AFollowTheLeaderMovement::BeginPlay()
{
	Super::BeginPlay();

	MovementSpeed = 250.0f;
}

void AFollowTheLeaderMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!LeaderActor)
		return;

	const FVector LeaderLocation = LeaderActor->GetActorLocation();

	if (FVector::Distance(GetActorLocation(), LeaderLocation) < MaxDistance)
		return;

	const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), LeaderLocation, DeltaTime, MovementSpeed);
	SetActorLocation(NewLocation);
}
