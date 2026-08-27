#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseActor.h"

#include "StopListening.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API AStopListening : public ABaseActor
{
	GENERATED_BODY()

public:
	AStopListening();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StopListening")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	uint8 Count = 0;

};