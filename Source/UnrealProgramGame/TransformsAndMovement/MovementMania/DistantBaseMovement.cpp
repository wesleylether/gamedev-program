#include "DistantBaseMovement.h"

ADistantBaseMovement::ADistantBaseMovement()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(RootComp);
}

void ADistantBaseMovement::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	DirectionVector = ArrowComponent->GetForwardVector();
}

void ADistantBaseMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceMoved = FVector::Distance(StartLocation, GetActorLocation());

	if (DistanceMoved >= DistanceThreshold)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance Moved: %f"), DistanceMoved);
		StartLocation = StartLocation + DirectionVector * DistanceThreshold;
		SetActorLocation(StartLocation);
		DirectionVector *= -1.0f;
	}

	const FVector Motion = DirectionVector * MovementSpeed * DeltaTime;
	SetActorLocation(GetActorLocation() + Motion);
}
