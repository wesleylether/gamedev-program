#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "BaseOverlapActor.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ABaseOverlapActor : public ABaseActor
{
	GENERATED_BODY()

public:
	ABaseOverlapActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<UBoxComponent> BoxComponent;

	UFUNCTION()
	virtual void HandleBoxComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleBoxComponentEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	static void PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp);
};