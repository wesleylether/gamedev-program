#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"
#include "TimerManager.h"

#include "RandomizeScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARandomizeScale : public ABaseMovementActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	FVector ScaleRange = FVector(1.0f, 1.0f, 1.0f);

private:
	void SetRandomScale();

	FTimerHandle RandomScaleTimerHandle;
};