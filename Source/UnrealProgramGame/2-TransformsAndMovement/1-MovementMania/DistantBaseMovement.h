#pragma once

#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"


#include "DistantBaseMovement.generated.h"

class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ADistantBaseMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ADistantBaseMovement();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector DirectionVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DistanceMoved = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceThreshold = 300.0f;
};