#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "FirstSweep.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AFirstSweep : public ABaseActor
{
	GENERATED_BODY()

public:
	AFirstSweep();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SweepDistance = 1000.0f;
};