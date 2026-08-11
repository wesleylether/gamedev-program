// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "StockKeeper.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AStockKeeper : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AStockKeeper();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<USceneComponent>> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PickupToSpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpawnPointCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RespawnDuration = 5.0f;

private:
	UPROPERTY()
	TMap<TObjectPtr<AActor>, FVector> SpawnedActorLocations;

	void SpawnPickup(FVector SpawnLocation);

	UFUNCTION()
	void OnDestroyed(AActor* DestroyedActor);
};