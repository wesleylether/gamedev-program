#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseActor.h"

#include "TimerDelegate.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ATimerDelegate : public ABaseActor
{
	GENERATED_BODY()

public:
	ATimerDelegate();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerDelegate")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void HandleTimer(const double WorldTime);
};