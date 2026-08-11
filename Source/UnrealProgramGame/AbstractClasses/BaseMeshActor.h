#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseMeshActor.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseMeshActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseMeshActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;
};