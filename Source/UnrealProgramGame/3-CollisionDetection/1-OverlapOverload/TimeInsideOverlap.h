#pragma once

#include "AbstractClasses/BaseOverlapActor.h"
#include "CoreMinimal.h"

#include "TimeInsideOverlap.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ATimeInsideOverlap : public ABaseOverlapActor
{
	GENERATED_BODY()

protected:
	virtual void HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeStarted = 0.0f;
};