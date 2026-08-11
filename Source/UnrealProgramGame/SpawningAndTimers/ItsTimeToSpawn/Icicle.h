#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "Icicle.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AIcicle : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AIcicle();

	void TurnPhysicsOn();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 5.0f;

	UFUNCTION()
	void OnTimerTimeout();
};