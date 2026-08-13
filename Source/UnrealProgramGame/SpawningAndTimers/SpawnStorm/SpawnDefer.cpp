#include "SpawnDefer.h"

#include "Components/BoxComponent.h"
#include "UnrealProgramGameCharacter.h"
#include "AbstractClasses/BaseSpawnObject.h"

ASpawnDefer::ASpawnDefer()
{
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetupAttachment(GetRootComponent());

	SpawnTarget = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnTarget"));
	SpawnTarget->SetupAttachment(GetRootComponent());
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
		Log(FString::Printf(TEXT("SpawnedActor is null in: %s"), *GetName()));
	}
	else
	{
		Log(FString::Printf(TEXT("SpawnedActor: %s"), *SpawnedActor->GetName()));
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
