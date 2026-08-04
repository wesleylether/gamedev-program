#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "FirstDelay.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AFirstDelay : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AFirstDelay();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayLength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength = 3.0f;

private:
	void RotateMesh();
};