#pragma once

#include "3-CollisionDetection/3-InteractableObjects/CoinPickup.h"
#include "CoreMinimal.h"

#include "GenerousCoin.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCollectedValue, int32, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCoinCollectedBy, AActor*, Collector, int32, Value);

UCLASS()
class UNREALPROGRAMGAME_API AGenerousCoin : public ACoinPickup
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnCoinCollectedValue OnCoinCollectedValue;

	UPROPERTY(BlueprintAssignable)
	FOnCoinCollectedBy OnCoinCollectedBy;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerousCoin")
	int32 CoinValue = 100.0f;

	virtual void CoinPickup(AActor* Collector) override;
};