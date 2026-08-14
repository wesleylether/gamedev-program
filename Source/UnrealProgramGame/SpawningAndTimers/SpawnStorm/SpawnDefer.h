
#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "SpawnDefer.generated.h"

class ABaseSpawnObject;
class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASpawnDefer : public ABaseActor
{
	GENERATED_BODY()

public:
	ASpawnDefer();

protected:
	virtual void BeginPlay() override;

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