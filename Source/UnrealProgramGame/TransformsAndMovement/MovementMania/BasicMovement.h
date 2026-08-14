#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "BasicMovement.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABasicMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ABasicMovement();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};