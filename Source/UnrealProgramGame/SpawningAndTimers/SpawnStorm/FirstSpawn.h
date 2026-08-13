#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "FirstSpawn.generated.h"

class ABaseSpawnObject;

UCLASS()
class UNREALPROGRAMGAME_API AFirstSpawn : public ABaseActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;
};