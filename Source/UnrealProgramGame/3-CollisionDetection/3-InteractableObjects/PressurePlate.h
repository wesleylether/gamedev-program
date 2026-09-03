#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"


#include "PressurePlate.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API APressurePlate : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	APressurePlate();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ActivationCount = 0;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool bIsActivated = false;

	FVector StartLocation;
	FVector EndLocation;
	FVector Destination;
};