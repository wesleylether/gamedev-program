#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FirstSpawn.generated.h"

class ABaseSpawnObject;

UCLASS()
class UNREALPROGRAMGAME_API AFirstSpawn : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;
};