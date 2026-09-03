#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "PingPongScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API APingPongScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	FVector MaxScale = FVector(3.0f, 3.0f, 3.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	FVector ScaleSpeed = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scaling Supreme")
	bool bUniform = false;

private:
	FVector BaseScale = FVector(1.0f, 1.0f, 1.0f);
	FVector TargetScale;
};