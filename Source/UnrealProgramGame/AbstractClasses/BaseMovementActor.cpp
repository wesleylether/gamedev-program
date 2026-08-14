#include "BaseMovementActor.h"

ABaseMovementActor::ABaseMovementActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseMovementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMovementActor::BeginPlay()
{
	Super::BeginPlay();
}
