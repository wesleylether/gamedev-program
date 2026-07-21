#pragma once

#include "Base/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "SplineBasedMovement.generated.h"

class USplineComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASplineBasedMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ASplineBasedMovement();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* SplineActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldLoop = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DistanceAlongSpline = 0.0f;
};