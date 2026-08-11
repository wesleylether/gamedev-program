#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseSpawnObject.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseSpawnObject : public AActor
{
	GENERATED_BODY()

public:
	ABaseSpawnObject();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;
};