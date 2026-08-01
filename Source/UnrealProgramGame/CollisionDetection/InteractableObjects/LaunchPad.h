#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "LaunchPad.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ALaunchPad : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	ALaunchPad();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LaunchVelocity = 500.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};