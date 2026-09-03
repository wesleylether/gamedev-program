#include "SpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "AbstractClasses/BaseSpawnObject.h"

ASpawnPoint::ASpawnPoint()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = ArrowComponent->GetComponentLocation();
	const FRotator Rotation = ArrowComponent->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnClass, &Location, &Rotation, SpawnParams);

	if (!SpawnedActor)
	{
		Log(FString::Printf(TEXT("Failed to spawn actor: %s"), *GetName()));
	}
}
