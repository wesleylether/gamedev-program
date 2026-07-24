#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "CurveScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ACurveScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scale Supreme")
	UCurveFloat* CurveScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scale Supreme")
	float MaxScale = 3.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CurveRotation")
	float CurveLength;

	FVector BaseScale;
	FVector TargetScale;
};