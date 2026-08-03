#include "SpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "SpawningAndTimers/Base/BaseSpawnObject.h"

ASpawnPoint::ASpawnPoint()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(SceneRootComponent);
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	const FVector  Location = ArrowComponent->GetComponentLocation();
	const FRotator Rotation = ArrowComponent->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnClass, &Location, &Rotation, SpawnParams);

	if (!SpawnedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor: %s"), *GetName());
	}
}
