#include "SpawnDefer.h"

#include "Components/BoxComponent.h"
#include "SpawningAndTimers/Base/BaseSpawnObject.h"
#include "UnrealProgramGameCharacter.h"

ASpawnDefer::ASpawnDefer()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetupAttachment(SceneRootComponent);

	SpawnTarget = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnTarget"));
	SpawnTarget->SetupAttachment(SceneRootComponent);
}

void ASpawnDefer::BeginPlay()
{
	Super::BeginPlay();

	if (!SpawnClass)
		return;

	SpawnBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawnDefer::OnBoxOverlap);

	SpawnedActor = GetWorld()->SpawnActorDeferred<ABaseSpawnObject>(
		SpawnClass,
		FTransform(),
		this,
		GetInstigator(),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	if (!SpawnedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnedActor is null in: %s"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Defer SpawnedActor: %s"), *GetName());
	}
}

void ASpawnDefer::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!SpawnedActor)
		return;

	if (!OtherActor || OtherActor == this)
		return;

	AUnrealProgramGameCharacter* Charactor = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Charactor)
		return;

	if (SpawnedActor && SpawnedActor->IsActorInitialized())
		return;

	FTransform SpawnTransform = SpawnTarget->GetComponentTransform();

	SpawnedActor->FinishSpawning(SpawnTransform);
}
