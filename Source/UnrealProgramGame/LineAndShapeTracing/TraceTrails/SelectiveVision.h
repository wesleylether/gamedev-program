#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "SelectiveVision.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ASelectiveVision : public ABaseActor
{
	GENERATED_BODY()

public:
	ASelectiveVision();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength = 1000.0f;
};