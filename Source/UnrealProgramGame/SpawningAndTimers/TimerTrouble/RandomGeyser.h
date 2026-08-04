#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "RandomGeyser.generated.h"

class UNiagaraSystem;
class USphereComponent;

UCLASS()
class UNREALPROGRAMGAME_API ARandomGeyser : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ARandomGeyser();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ExplosionFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EruptionStrength = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSeconds = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSeconds = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoStart = false;

private:
	FTimerHandle TimerHandle;

	void SetTimer();
	void Errupt();
};