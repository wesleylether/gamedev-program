#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "ZeppelinBomber.generated.h"

class UArrowComponent;
class ACannonBall;
class USplineComponent;

UCLASS()
class UNREALPROGRAMGAME_API AZeppelinBomber : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AZeppelinBomber();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACannonBall> Bomb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BombSpawnInterval = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> SplineActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldLoop = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> SplineComponent;

private:
	FTimerHandle BombSpawnTimer;
	float DistanceAlongSpline = 0.0f;

	UFUNCTION()
	void SpawnBomb();
};