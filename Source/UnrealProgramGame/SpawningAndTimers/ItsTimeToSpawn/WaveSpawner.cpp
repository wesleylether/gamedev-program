#include "WaveSpawner.h"

#include "Components/BoxComponent.h"
#include "UnrealProgramGameCharacter.h"

AWaveSpawner::AWaveSpawner()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(SceneRoot);
}

void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();

	CurrentWaveIndex = 0;

	Box->OnComponentBeginOverlap.AddDynamic(this, &AWaveSpawner::OnOverlapBegin);
}

void AWaveSpawner::RunWave(int32 WaveIndex)
{
	FWave wave = Waves[WaveIndex];

	if (wave.WaveActorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave %d has no actor class"), WaveIndex);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Running wave %d!"), WaveIndex + 1);

	CurrentSpawnCount = 0;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveSpawner::SpawnNextActor, wave.ActorSpawnInterval, true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWaveSpawner::OnWaveDurationEnded, wave.WaveDuration, false);
	UE_LOG(LogTemp, Warning, TEXT("Next wave in %f seconds"), wave.WaveDuration);
}

void AWaveSpawner::SpawnNextActor()
{
	FWave wave = Waves[CurrentWaveIndex];

	if (CurrentSpawnCount >= wave.ActorAmount)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector SpawnLocation = GetActorLocation();
	SpawnLocation += CurrentSpawnCount * wave.ActorOffset;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	AActor* Spawned = GetWorld()->SpawnActor(wave.WaveActorClass, &SpawnLocation, &SpawnRotation, SpawnParams);

	if (wave.ActorLifespan >= 0.0f)
	{
		Spawned->SetLifeSpan(wave.ActorLifespan);
	}

	CurrentSpawnCount++;
}

void AWaveSpawner::OnWaveDurationEnded()
{
	CurrentWaveIndex++;

	if (CurrentWaveIndex >= Waves.Num())
	{
		bWaveActive = false;
		UE_LOG(LogTemp, Warning, TEXT("No more waves"));
		return;
	}

	RunWave(CurrentWaveIndex);
}

void AWaveSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bWaveActive)
		return;

	if (!OtherActor || OtherActor == this)
		return;

	if (const AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor); !Character)
		return;

	if (Waves.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No waves defined"));
		return;
	}

	bWaveActive = true;
	CurrentWaveIndex = 0;
	RunWave(CurrentWaveIndex);
}
