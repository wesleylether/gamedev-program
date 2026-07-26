#pragma once

#include "CollisionDetection/Base/BaseOverlapActor.h"
#include "CoreMinimal.h"

#include "CounterOverlap.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ACounterOverlap : public ABaseOverlapActor
{
	GENERATED_BODY()
	
public:
	ACounterOverlap();

protected:
	virtual void HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> OverlappedActors;
};