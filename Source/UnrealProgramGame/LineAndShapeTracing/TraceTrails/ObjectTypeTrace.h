
#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "ObjectTypeTrace.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AObjectTypeTrace : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AObjectTypeTrace();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 100.0f;
};