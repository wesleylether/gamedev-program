#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseActor.h"

#include "BuddyWatcher.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABuddyWatcher : public ABaseActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuddyWatcher")
	TObjectPtr<AActor> Buddy;
	
	UFUNCTION()
	void OnDestroyed(AActor* DestroyedActor);
};