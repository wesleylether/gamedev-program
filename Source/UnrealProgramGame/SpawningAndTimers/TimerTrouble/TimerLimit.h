#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "TimerLimit.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ATimerLimit : public ABaseMeshActor
{
	GENERATED_BODY()

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