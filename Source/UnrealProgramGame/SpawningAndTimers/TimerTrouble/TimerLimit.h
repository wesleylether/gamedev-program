#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "TimerLimit.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ATimerLimit : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ATimerLimit();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimerLimit = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TimerCount = 0;

private:
	FTimerHandle TimerHandle;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	void ChangeColor();
};