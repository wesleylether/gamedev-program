
#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMeshActor.h"

#include "TownCrierOne.generated.h"

class ATheTownCrier;

UCLASS()
class UNREALPROGRAMGAME_API ATownCrierOne : public ABaseMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TownCrierOne")
	TObjectPtr<ATheTownCrier> TownCrier;

	UFUNCTION()
	void ChangeColor();
};