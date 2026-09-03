#pragma once

#include "AbstractClasses/BaseMovementActor.h"

#include "CoreMinimal.h"

#include "SpeedCurveMovement.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ASpeedCurveMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TObjectPtr<UCurveFloat> SpeedCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float InterpolationSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector EndLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurveLength;

	FVector Destination;
};