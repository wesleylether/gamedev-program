#pragma once

#include "CoreMinimal.h"
#include "AbstractClasses/BaseMeshActor.h"

#include "TheTownCrier.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeakUpSignature);

UCLASS()
class UNREALPROGRAMGAME_API ATheTownCrier : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ATheTownCrier();
	
	UPROPERTY(BlueprintAssignable)
	FOnSpeakUpSignature OnSpeakUp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};