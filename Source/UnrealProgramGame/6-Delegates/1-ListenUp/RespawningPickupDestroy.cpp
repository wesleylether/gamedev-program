// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawningPickupDestroy.h"

ARespawningPickupDestroy::ARespawningPickupDestroy()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(GetRootComponent());
}

void ARespawningPickupDestroy::BeginPlay()
{
	Super::BeginPlay();

	SpawnPickup();
}

void ARespawningPickupDestroy::SpawnPickup()
{
	if (!PickupToSpawnClass || !TargetComponent)
		return;

	if (RespawnLimit > -1)
	{
		if (RespawnCount >= RespawnLimit)
		{
			Log(FString::Printf(TEXT("Respawn limit reached in %s"), *GetName()));
			return;
		}
	}

	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnLocation = TargetComponent->GetComponentLocation();
	const FRotator SpawnRotation = TargetComponent->GetComponentRotation();
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PickupToSpawnClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedActor)
	{
		Pickup = SpawnedActor;
		Pickup->OnDestroyed.AddDynamic(this, &ARespawningPickupDestroy::OnDestroyed);
		RespawnCount++;
	}
}

void ARespawningPickupDestroy::OnDestroyed(AActor* DestroyedActor)
{
	Pickup = nullptr;

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ARespawningPickupDestroy::SpawnPickup, RespawnDuration);
}
