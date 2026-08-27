#pragma once

#include "AbstractClasses/BaseMovementActor.h"

#include "CoreMinimal.h"

#include "InterpolatedMovement.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AInterpolatedMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AInterpolatedMovement();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> StartActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> EndActor;

private:
	bool bMovingToEnd = true;
};