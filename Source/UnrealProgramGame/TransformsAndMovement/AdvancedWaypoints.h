
#pragma once

#include "Base/BaseMovementActor.h"
#include "CoreMinimal.h"

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
	TArray<AActor*> Waypoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* CurrentWaypoint;

	int CurrentWaypointIndex = 0;
};