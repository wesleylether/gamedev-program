#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseOverlapActor.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class UNREALPROGRAMGAME_API ABaseOverlapActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseOverlapActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USceneComponent> RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UFUNCTION()
	virtual void HandleBoxComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex,
		bool				 bFromSweep,
		const FHitResult&	 SweepResult);

	UFUNCTION()
	virtual void HandleBoxComponentEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex);

	static void PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp);
};