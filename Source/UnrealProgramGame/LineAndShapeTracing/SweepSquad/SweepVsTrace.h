#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "SweepVsTrace.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ASweepVsTrace : public ABaseActor
{
	GENERATED_BODY()

public:
	ASweepVsTrace();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SweepDistance = 1000.0f;
};