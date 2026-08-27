#include "DistanceBasedScale.h"

ADistanceBasedScale::ADistanceBasedScale()
{
}

void ADistanceBasedScale::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(TargetActor))
		return;

	BaseLocation = GetActorLocation();
	TargetLocation = TargetActor->GetActorLocation();
	ScaleTargetLocation = TargetLocation;

	SetActorScale3D(FVector(MinScale));
}

void ADistanceBasedScale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(TargetActor))
		return;

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed);
	SetActorLocation(NewLocation);

	const float MaxDistance = FVector::Distance(BaseLocation, ScaleTargetLocation);
	const float CurrentDistanceFromBase = FVector::Distance(BaseLocation, NewLocation);
	const float Alpha = MaxDistance > KINDA_SMALL_NUMBER
		? FMath::Clamp(CurrentDistanceFromBase / MaxDistance, 0.0f, 1.0f)
		: 0.0f;
	const float NewScale = FMath::Lerp(MinScale, MaxScale, Alpha);
	SetActorScale3D(FVector(NewScale));

	if (NewLocation.Equals(TargetLocation))
	{
		if (TargetLocation.Equals(TargetActor->GetActorLocation()))
		{
			TargetLocation = BaseLocation;
		}
		else if (TargetLocation.Equals(BaseLocation))
		{
			TargetLocation = TargetActor->GetActorLocation();
			ScaleTargetLocation = TargetLocation;
		}
	}
}
