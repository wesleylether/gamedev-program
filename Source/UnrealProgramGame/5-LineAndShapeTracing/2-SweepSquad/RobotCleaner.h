#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "RobotCleaner.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARobotCleaner : public ABaseActor
{
	GENERATED_BODY()

public:
	ARobotCleaner();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RobotCleaner")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RobotCleaner")
	float Speed = 105.0f;
};