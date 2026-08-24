#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "MultiSweep.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AMultiSweep : public ABaseActor
{
	GENERATED_BODY()

public:
	AMultiSweep();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength = 1000.0f;
};