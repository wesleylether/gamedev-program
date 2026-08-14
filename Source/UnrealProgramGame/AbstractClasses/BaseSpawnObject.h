#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "BaseSpawnObject.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseSpawnObject : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ABaseSpawnObject();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const { return Mesh; }
};