
#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "NonUniformScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ANonUniformScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	FVector MaxScale = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	FVector ScaleSpeed = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	bool bInterpolation = true;

	void ManualScale(float DeltaTime);
	void InterpolationScale(float DeltaTime);

private:
	FTimerHandle RandomScaleTimerHandle;

	void SetRandomValues();
};