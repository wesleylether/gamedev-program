#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "FirstTrace.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AFirstTrace : public ABaseActor
{
	GENERATED_BODY()

public:
	AFirstTrace();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength = 1000.0f;
};