#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"


#include "ImpactPoint.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AImpactPoint : public ABaseMovementActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};