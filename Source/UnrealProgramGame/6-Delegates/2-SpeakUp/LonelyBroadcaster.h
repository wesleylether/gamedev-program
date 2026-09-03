#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "LonelyBroadcaster.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLonelyBroadcastSignature);

UCLASS()
class UNREALPROGRAMGAME_API ALonelyBroadcaster : public ABaseActor
{
	GENERATED_BODY()

public:
	ALonelyBroadcaster();

	UPROPERTY(BlueprintAssignable, Category = "LonelyBroadcaster")
	FOnLonelyBroadcastSignature OnLonelyBroadcast;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LonelyBroadcaster")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};