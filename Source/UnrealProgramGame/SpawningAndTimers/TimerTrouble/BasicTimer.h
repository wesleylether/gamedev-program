#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "BasicTimer.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABasicTimer : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ABasicTimer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength = 3.0f;

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	void ChangeColor();
};