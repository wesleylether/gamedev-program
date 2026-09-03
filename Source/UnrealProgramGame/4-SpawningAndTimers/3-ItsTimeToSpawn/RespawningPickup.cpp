// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawningPickup.h"

ARespawningPickup::ARespawningPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(GetRootComponent());
}

void ARespawningPickup::BeginPlay()
{
	Super::BeginPlay();

	SpawnPickup();
}

void ARespawningPickup::SpawnPickup()
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
		Pickup->OnDestroyed.AddDynamic(this, &ARespawningPickup::OnDestroyed);
		RespawnCount++;
	}
}

void ARespawningPickup::OnDestroyed(AActor* DestroyedActor)
{
	Pickup = nullptr;

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ARespawningPickup::SpawnPickup, RespawnDuration);
}
