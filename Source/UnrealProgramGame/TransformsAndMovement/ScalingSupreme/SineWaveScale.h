#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "SineWaveScale.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ASineWaveScale : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scale Supreme")
	FVector MaxScale = FVector(3.0f, 3.0f, 3.0f);

	FVector BaseScale;
	FVector TargetScale;
};