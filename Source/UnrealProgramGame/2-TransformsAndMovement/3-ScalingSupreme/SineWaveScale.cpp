#include "SineWaveScale.h"

void ASineWaveScale::BeginPlay()
{
	Super::BeginPlay();

	BaseScale = GetActorScale3D();
	TargetScale = MaxScale;
}

void ASineWaveScale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float	ScaleFactor = FMath::Sin(GetWorld()->GetTimeSeconds()) * 0.5f + 0.5f;
	FVector NewScale = FMath::Lerp(BaseScale, TargetScale, ScaleFactor);
	SetActorScale3D(NewScale);
}
