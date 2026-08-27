#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "ContinuousRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AContinuousRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};