#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "OrbitRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AOrbitRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AOrbitRotation();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> SecondStaticMesh;
};