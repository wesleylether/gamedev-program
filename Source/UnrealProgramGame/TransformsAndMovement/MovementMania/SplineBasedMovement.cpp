#include "SplineBasedMovement.h"

#include "Components/SplineComponent.h"

ASplineBasedMovement::ASplineBasedMovement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASplineBasedMovement::BeginPlay()
{
	Super::BeginPlay();

	MovementSpeed = 200.0f;

	if (SplineActor)
	{
		SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();
	}
}

void ASplineBasedMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SplineActor || !SplineComponent)
		return;

	const FTransform Transform = SplineComponent->GetTransformAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
	const FTransform NewTransform = FTransform(Transform.GetRotation(), Transform.GetLocation(), GetActorScale3D());

	SetActorTransform(NewTransform);

	DistanceAlongSpline += DeltaTime * MovementSpeed;

	if (bShouldLoop)
	{
		if (DistanceAlongSpline > SplineComponent->GetSplineLength())
		{
			DistanceAlongSpline = 0.0f;
		}
	}
}
