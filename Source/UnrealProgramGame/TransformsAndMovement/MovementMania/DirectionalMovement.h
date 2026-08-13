#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"

#include "DirectionalMovement.generated.h"

class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ADirectionalMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ADirectionalMovement();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;
};