#include "AdvancedWaypoints.h"

AAdvancedWaypoints::AAdvancedWaypoints()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAdvancedWaypoints::BeginPlay()
{
	Super::BeginPlay();

	MovementSpeed = 200.0f;

	if (Waypoints.Num() > 0)
	{
		CurrentWaypoint = Waypoints[CurrentWaypointIndex];
		CurrentWaypointIndex++;
	}
}

void AAdvancedWaypoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Waypoints.Num() == 0)
		return;

	if (CurrentWaypoint)
	{
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), CurrentWaypoint->GetActorLocation(), DeltaTime, MovementSpeed);
		SetActorLocation(NewLocation);

		if (GetActorLocation().Equals(CurrentWaypoint->GetActorLocation()))
		{
			if (CurrentWaypointIndex < Waypoints.Num())
			{
				CurrentWaypoint = Waypoints[CurrentWaypointIndex];

				if (CurrentWaypointIndex == Waypoints.Num() - 1)
				{
					CurrentWaypointIndex = 0;
				}
				else
				{
					CurrentWaypointIndex++;
				}
			}
		}
	}
}
