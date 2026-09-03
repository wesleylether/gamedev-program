#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "WaveSpawner.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<AActor> WaveActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 ActorAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	FVector ActorOffset = FVector(0.0f, 100.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float ActorLifespan = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float ActorSpawnInterval = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveDuration = 10.0f;
};

UCLASS()
class UNREALPROGRAMGAME_API AWaveSpawner : public ABaseActor
{
	GENERATED_BODY()

public:
	AWaveSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TArray<FWave> Waves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Waves")
	int32 CurrentWaveIndex = 0;
	FTimerHandle SpawnTimerHandle;
	int32 CurrentSpawnCount = 0;

	bool bWaveActive = false;

	void RunWave(int32 WaveIndex);
	void SpawnNextActor();

	UFUNCTION()
	void OnWaveDurationEnded();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};