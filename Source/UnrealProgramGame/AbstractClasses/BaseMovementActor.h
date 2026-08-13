#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "BaseMovementActor.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseMovementActor : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ABaseMovementActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 100.0f;
};