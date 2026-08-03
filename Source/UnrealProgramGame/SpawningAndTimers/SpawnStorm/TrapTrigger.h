
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TrapTrigger.generated.h"

class UArrowComponent;
class ABaseSpawnObject;
class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ATrapTrigger : public AActor
{
	GENERATED_BODY()

public:
	ATrapTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> TrapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> SpawnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTriggerOnce = false;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bHasTriggered = false;
};