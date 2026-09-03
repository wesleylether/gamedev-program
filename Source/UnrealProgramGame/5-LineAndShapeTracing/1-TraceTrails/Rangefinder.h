#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "Rangefinder.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARangefinder : public ABaseActor
{
	GENERATED_BODY()

public:
	ARangefinder();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRange = 1000.0f;
};