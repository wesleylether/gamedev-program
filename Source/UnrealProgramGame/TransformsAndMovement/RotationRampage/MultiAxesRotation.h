#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "MultiAxesRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AMultiAxesRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float YawSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PitchSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RollSpeed = 100.0f;
};