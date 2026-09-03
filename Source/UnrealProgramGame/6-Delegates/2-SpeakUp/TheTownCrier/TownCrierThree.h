#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "TownCrierThree.generated.h"

class ATheTownCrier;

UCLASS()
class UNREALPROGRAMGAME_API ATownCrierThree : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ATownCrierThree();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TownCrierOne")
	TObjectPtr<ATheTownCrier> TownCrier;

	UFUNCTION()
	void Jump();
};