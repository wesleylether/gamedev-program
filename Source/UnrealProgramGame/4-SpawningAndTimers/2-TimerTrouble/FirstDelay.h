#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "FirstDelay.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AFirstDelay : public ABaseMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayLength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength = 3.0f;

private:
	void RotateMesh();
};