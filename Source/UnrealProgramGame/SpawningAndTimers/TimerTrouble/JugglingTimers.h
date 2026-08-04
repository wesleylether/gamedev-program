#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "JugglingTimers.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AJugglingTimers : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AJugglingTimers();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColorTimerLength = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LogTimerLength = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimerLength = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> SpawnedMesh;

private:
	FTimerHandle ColorTimerHandle;
	FTimerHandle LogTimerHandle;
	FTimerHandle SpawnTimerHandle;

	void ChangeColor();
	void LogMessage();
	void SpawnActor();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
};