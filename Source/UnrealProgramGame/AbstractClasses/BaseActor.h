#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseActor.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;
};