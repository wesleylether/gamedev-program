// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "RespawningPickupDestroy.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARespawningPickupDestroy : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ARespawningPickupDestroy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> TargetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PickupToSpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RespawnDuration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RespawnLimit = -1;

private:
	int32 RespawnCount = 0;
	TObjectPtr<AActor> Pickup = nullptr;
	FTimerHandle RespawnTimerHandle;

	void SpawnPickup();

	UFUNCTION()
	void OnDestroyed(AActor* DestroyedActor);
};