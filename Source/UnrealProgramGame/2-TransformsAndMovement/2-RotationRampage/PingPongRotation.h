#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "PingPongRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API APingPongRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationAmount = 360.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed = 100.0f;

	float RotationLeft;

	int32 RotationDirection = 1;
};