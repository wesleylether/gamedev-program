#include "FirstDelay.h"
#include "Math/UnrealMathUtility.h"

AFirstDelay::AFirstDelay()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFirstDelay::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFirstDelay::RotateMesh, TimerLength, true, DelayLength);
}

void AFirstDelay::RotateMesh()
{
	FRotator RandomRotation = FRotator(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
	StaticMesh->SetRelativeRotation(RandomRotation);
}
