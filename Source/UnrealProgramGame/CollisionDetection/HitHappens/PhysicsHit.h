#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"


#include "PhysicsHit.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API APhysicsHit : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	APhysicsHit();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};