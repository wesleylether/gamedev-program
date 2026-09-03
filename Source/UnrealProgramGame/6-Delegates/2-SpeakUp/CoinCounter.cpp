
#include "CoinCounter.h"

#include "Components/TextRenderComponent.h"
#include "GenerousCoin.h"
#include "Kismet/GameplayStatics.h"

ACoinCounter::ACoinCounter()
{
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetVerticalAlignment(EVRTA_TextCenter);
	Text->SetupAttachment(RootComponent);

	Text->SetText(FText::FromString("Total Coin value: 0"));
}

void ACoinCounter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerousCoin::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		if (AGenerousCoin* GenerousCoin = Cast<AGenerousCoin>(Actor))
		{
			GenerousCoin->OnCoinCollectedValue.AddUniqueDynamic(this, &ACoinCounter::OnCoinCollectedWithValue);
			GenerousCoin->OnCoinCollectedBy.AddUniqueDynamic(this, &ACoinCounter::OnCoinCollectedWithCollector);
		}
	}
}

void ACoinCounter::OnCoinCollectedWithValue(int32 CoinValue)
{
	CollectCoin(CoinValue);

	Log(FString::Printf(TEXT("%s: Collecting coin of value %d"), *GetActorNameOrLabel(), CoinValue));
}

void ACoinCounter::OnCoinCollectedWithCollector(AActor* Collector, int32 CoinValue)
{
	CollectCoin(CoinValue);

	Log(FString::Printf(TEXT("%s: %s is collecting coin of value %d"), *GetActorNameOrLabel(), *Collector->GetActorNameOrLabel(), CoinValue));
}

void ACoinCounter::CollectCoin(int32 CoinValue)
{
	TotalCoins += CoinValue;

	const FString NewTextString = FString::Printf(TEXT("Total Coin value: %d"), TotalCoins);
	Text->SetText(FText::FromString(NewTextString));
}
