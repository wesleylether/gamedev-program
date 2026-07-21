#pragma once

#include "Base/BaseMovementActor.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"

#include "DistantBaseMovement.generated.h"

class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ADistantBaseMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ADistantBaseMovement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector DirectionVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DistanceMoved = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceThreshold = 300.0f;
};