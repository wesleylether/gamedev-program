
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpawnDefer.generated.h"

class ABaseSpawnObject;
class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASpawnDefer : public AActor
{
	GENERATED_BODY()

public:
	ASpawnDefer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> SpawnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TObjectPtr<ABaseSpawnObject> SpawnedActor;
};