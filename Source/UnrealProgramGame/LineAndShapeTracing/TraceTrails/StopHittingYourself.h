#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "StopHittingYourself.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AStopHittingYourself : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AStopHittingYourself();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength = 1000.0f;
};