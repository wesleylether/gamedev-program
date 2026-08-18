#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "CurveRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ACurveRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveRotation")
	TObjectPtr<UCurveFloat> CurveFloat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CurveRotation")
	float CurveLength;
};