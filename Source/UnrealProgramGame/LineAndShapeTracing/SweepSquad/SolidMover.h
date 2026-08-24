#pragma once

#include "AbstractClasses/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "SolidMover.generated.h"

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
	float MovementSpeed = 150.0f;
	
	bool bForward = true;
};