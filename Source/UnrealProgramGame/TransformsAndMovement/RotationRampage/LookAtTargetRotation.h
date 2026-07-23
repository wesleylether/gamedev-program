#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "LookAtTargetRotation.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ALookAtTargetRotation : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation")
	AActor* TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation")
	float InterpolationSpeed = 4.0f;
};