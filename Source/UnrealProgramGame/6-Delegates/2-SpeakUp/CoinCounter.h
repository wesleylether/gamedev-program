
#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "CoinCounter.generated.h"

class UTextRenderComponent;

UCLASS()
class UNREALPROGRAMGAME_API ACoinCounter : public ABaseActor
{
	GENERATED_BODY()

public:
	ACoinCounter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinCounter")
	UTextRenderComponent* Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoinCounter")
	int32 TotalCoins = 0;

	UFUNCTION()
	void OnCoinCollectedWithValue(int32 CoinValue);

	UFUNCTION()
	void OnCoinCollectedWithCollector(AActor* Collector, int32 CoinValue);
	
	void CollectCoin(int32 CoinValue);
};