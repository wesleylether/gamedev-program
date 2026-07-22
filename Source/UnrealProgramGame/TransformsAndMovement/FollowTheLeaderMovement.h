#pragma once

#include "Base/BaseMovementActor.h"
#include "CoreMinimal.h"

#include "FollowTheLeaderMovement.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AFollowTheLeaderMovement : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Follow The Leader")
	AActor* LeaderActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Follow The Leader")
	float MaxDistance = 200.0f;
};