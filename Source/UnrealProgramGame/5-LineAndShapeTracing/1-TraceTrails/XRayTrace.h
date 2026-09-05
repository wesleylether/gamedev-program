#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "XRayTrace.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AXRayTrace : public ABaseActor
{
	GENERATED_BODY()

public:
	AXRayTrace();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength = 1000.0f;
};