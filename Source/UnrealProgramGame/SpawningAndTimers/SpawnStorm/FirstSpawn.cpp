#include "FirstSpawn.h"

#include "SpawningAndTimers/Base/BaseSpawnObject.h"

void AFirstSpawn::BeginPlay()
{
	Super::BeginPlay();

	const FVector  Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnClass, &Location, &Rotation, SpawnParams);

	if (!SpawnedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor: %s"), *GetName());
	}
}
