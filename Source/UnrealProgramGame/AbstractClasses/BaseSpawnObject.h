#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"
#include "LineAndShapeTracing/LookAndInteract/Interactable.h"

#include "BaseSpawnObject.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseSpawnObject : public ABaseMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	ABaseSpawnObject();
	
	virtual void Interact_Implementation(APawn* InteractingPawn) override;

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const { return Mesh; }
};