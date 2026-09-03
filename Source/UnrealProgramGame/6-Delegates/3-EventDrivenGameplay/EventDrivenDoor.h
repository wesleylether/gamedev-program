#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "EventDrivenDoor.generated.h"

class AEventDriverPressurePlate;

UCLASS()
class UNREALPROGRAMGAME_API AEventDrivenDoor : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AEventDrivenDoor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventDrivenDoor")
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventDrivenDoor")
	TArray<TObjectPtr<AEventDriverPressurePlate>> PressurePlates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventDrivenDoor")
	float DoorSpeed = 10.0f;

	UFUNCTION()
	void OnPressurePlatePressed();

	UFUNCTION()
	void OnPressurePlateReleased();

	UFUNCTION()
	void OpenDoor();

	UFUNCTION()
	void CloseDoor();

private:
	bool bIsActivated = false;
	int32 DoorActivatedCount = 0;
	FVector DoorStartLocation;
	FVector DoorEndLocation;
	FVector DoorDestination;
};