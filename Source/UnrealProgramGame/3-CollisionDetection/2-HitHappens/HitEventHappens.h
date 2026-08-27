#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"


#include "HitEventHappens.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AHitEventHappens : public ABaseMovementActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};