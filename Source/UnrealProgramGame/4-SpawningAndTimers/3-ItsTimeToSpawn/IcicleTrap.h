#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "IcicleTrap.generated.h"

class UArrowComponent;
class AIcicle;
class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API AIcicleTrap : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AIcicleTrap();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icicle Trap")
	TObjectPtr<UBoxComponent> BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icicle Trap")
	TObjectPtr<UArrowComponent> SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icicle Trap")
	TSubclassOf<AIcicle> Icicle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icicle Trap")
	float TrapActivateDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icicle Trap")
	float RespawnDelay = 5.0f;

private:
	bool bIsActivated = false;
	TObjectPtr<AIcicle> ActiveIcicle;
	FTimerHandle TrapActivateTimer;
	FTimerHandle RespawnTimer;

	void SpawnIcicle();

	UFUNCTION()
	void HandleTrapActivate();

	UFUNCTION()
	void HandleRespawn();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};