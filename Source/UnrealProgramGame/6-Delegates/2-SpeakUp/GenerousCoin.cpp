
#include "GenerousCoin.h"

void AGenerousCoin::BeginPlay()
{
	Super::BeginPlay();
}

void AGenerousCoin::CoinPickup(AActor* Collector)
{
	if (bIsCollected)
		return;

	Log(FString::Printf(TEXT("%s: Broadcasting OnCoinCollectedValue"), *GetActorNameOrLabel()));
	OnCoinCollectedValue.Broadcast(CoinValue);

	Log(FString::Printf(TEXT("%s: Broadcasting OnCoinCollectedBy"), *GetActorNameOrLabel()));
	OnCoinCollectedBy.Broadcast(Collector, CoinValue);

	Super::CoinPickup(Collector);
}

void AGenerousCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
