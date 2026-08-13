#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpawnPoint.generated.h"

class ABaseSpawnObject;
class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASpawnPoint : public ABaseActor
{
	GENERATED_BODY()

public:
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseSpawnObject> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> ArrowComponent;
};