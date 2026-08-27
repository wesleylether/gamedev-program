// Fill out your copyright notice in the Description page of Project Settings.

#include "StockKeeper.h"

AStockKeeper::AStockKeeper()
{
	for (int32 i = 0; i < SpawnPointCount; ++i)
	{
		FString PickupName = FString::Printf(TEXT("SpawnPoint %d"), i);
		USceneComponent* SpawnPoint = CreateDefaultSubobject<USceneComponent>(*PickupName);
		SpawnPoint->SetupAttachment(GetRootComponent());

		SpawnPoints.Add(SpawnPoint);
	}
}

void AStockKeeper::BeginPlay()
{
	Super::BeginPlay();

	if (!PickupToSpawnClass)
		return;

	for (const USceneComponent* SpawnPoint : SpawnPoints)
	{
		SpawnPickup(SpawnPoint->GetComponentLocation());
	}
}

void AStockKeeper::SpawnPickup(FVector SpawnLocation)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FRotator SpawnRotation = FRotator::ZeroRotator;
	AActor* SpawnedActor = GetWorld()->SpawnActor(PickupToSpawnClass, &SpawnLocation, &SpawnRotation, SpawnParams);

	if (SpawnedActor)
	{
		SpawnedActorLocations.Add(SpawnedActor, SpawnLocation);
		SpawnedActor->OnDestroyed.AddDynamic(this, &AStockKeeper::OnDestroyed);
	}
}

void AStockKeeper::OnDestroyed(AActor* DestroyedActor)
{
	if (FVector* FoundLocation = SpawnedActorLocations.Find(DestroyedActor))
	{
		const FVector InitialSpawnLocation = *FoundLocation;
		SpawnedActorLocations.Remove(DestroyedActor);

		const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AStockKeeper::SpawnPickup, InitialSpawnLocation);

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, TimerDelegate, RespawnDuration, false);
	}
}
