#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

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
	UStaticMeshComponent* SecondStaticMesh;
};