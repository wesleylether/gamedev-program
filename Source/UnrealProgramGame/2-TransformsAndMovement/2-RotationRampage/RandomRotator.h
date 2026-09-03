#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "RandomRotator.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARandomRotator : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	FRotator Rotation;
};