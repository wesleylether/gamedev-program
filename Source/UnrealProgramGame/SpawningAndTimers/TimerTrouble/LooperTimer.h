#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "LooperTimer.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ALooperTimer : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ALooperTimer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength = 3.0f;

private:
	void ChangeColor();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
};