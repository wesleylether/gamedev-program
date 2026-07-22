#pragma once

#include "TransformsAndMovement/Base/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "SineWaveMovement.generated.h"

class ATargetPoint;

UCLASS()
class UNREALPROGRAMGAME_API ASineWaveMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATargetPoint* TargetActor;

	FVector StartLocation;
	FVector EndLocation;
};