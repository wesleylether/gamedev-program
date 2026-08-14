#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "CountDownBomb.generated.h"

class URadialForceComponent;
class UNiagaraSystem;

UCLASS()
class UNREALPROGRAMGAME_API ACountDownBomb : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ACountDownBomb();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BombTimerDuration = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> BombSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> BombEffect;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionForce;

private:
	FTimerHandle BombTimer;

	void BombTimerCallback();
};