#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "SolidMover.generated.h"

class UArrowComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASolidMover : public ABaseActor
{
	GENERATED_BODY()

public:
	ASolidMover();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolidMover")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolidMover")
	TObjectPtr<UArrowComponent> Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolidMover")
	float MovementSpeed = 150.0f;
	
};