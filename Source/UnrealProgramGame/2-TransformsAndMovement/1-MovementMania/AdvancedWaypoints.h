
#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMovementActor.h"

#include "AdvancedWaypoints.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AAdvancedWaypoints : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AAdvancedWaypoints();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
	TArray<TObjectPtr<AActor>> Waypoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> CurrentWaypoint;

	int CurrentWaypointIndex = 0;
};