#pragma once

#include "BaseActor.h"
#include "CoreMinimal.h"

#include "BaseMeshActor.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseMeshActor : public ABaseActor
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