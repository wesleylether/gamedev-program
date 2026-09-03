#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "EventDriverPressurePlate.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressurePlatePressedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressurePlateReleasedSignature);

UCLASS()
class UNREALPROGRAMGAME_API AEventDriverPressurePlate : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AEventDriverPressurePlate();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable)
	FOnPressurePlatePressedSignature OnPressurePlatePressed;

	UPROPERTY(BlueprintAssignable)
	FOnPressurePlateReleasedSignature OnPressurePlateReleased;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventDriverPressurePlate")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool bActivated = false;
	FVector StartLocation;
	FVector EndLocation;
	FVector Destination;
};