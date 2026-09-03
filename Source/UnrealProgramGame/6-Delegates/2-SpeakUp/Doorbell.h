#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "Doorbell.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorbellRungSignature);

UCLASS()
class UNREALPROGRAMGAME_API ADoorbell : public ABaseMeshActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDoorbellRungSignature OnDoorbellRung;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};