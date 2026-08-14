#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "UniformScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AUniformScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AUniformScale();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	float MaxScale = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	float ScaleSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	bool bInterpolation = true;

	void ManualScale(float DeltaTime);
	void InterpolationScale(float DeltaTime);
};