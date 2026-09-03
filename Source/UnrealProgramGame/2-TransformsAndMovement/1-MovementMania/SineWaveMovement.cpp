#include "SineWaveMovement.h"

#include "Engine/TargetPoint.h"

void ASineWaveMovement::BeginPlay()
{
	Super::BeginPlay();

	if (!TargetActor)
		return;

	StartLocation = GetActorLocation();
	EndLocation = TargetActor->GetActorLocation();
}

void ASineWaveMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor)
		return;

	const double SineValue = FMath::Sin(GetWorld()->GetTimeSeconds());
	const float	 SineNormalized = (SineValue + 1.0f) / 2.0f;

	const FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, SineNormalized);
	SetActorLocation(NewLocation);
}
