#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseActor.h"

#include "ZoneWatcher.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AZoneWatcher : public ABaseActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneWatcher")
	TObjectPtr<AActor> Target;
	
	UFUNCTION()
	void OnTargetOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTargetEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};