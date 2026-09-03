#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "DestructionZone.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ADestructionZone : public ABaseActor
{
	GENERATED_BODY()

public:
	ADestructionZone();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> DestructionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};