
#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "TrafficLight.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ATrafficLight : public ABaseMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenTimerLength = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YellowTimerLength = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RedTimerLength = 4.0f;

private:
	void ChangeColorToGreen();
	void ChangeColorToYellow();
	void ChangeColorToRed();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
};