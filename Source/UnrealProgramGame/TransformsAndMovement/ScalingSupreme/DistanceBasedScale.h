#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "DistanceBasedScale.generated.h"

class AActor;

UCLASS()
class UNREALPROGRAMGAME_API ADistanceBasedScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ADistanceBasedScale();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme|Target")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme|Scale")
	float MinScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme|Scale")
	float MaxScale = 3.0f;

private:
	FVector BaseLocation;
	FVector TargetLocation;
	FVector ScaleTargetLocation;
};