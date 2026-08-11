#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpawnPoint.generated.h"

class ABaseSpawnObject;
class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> ArrowComponent;
};