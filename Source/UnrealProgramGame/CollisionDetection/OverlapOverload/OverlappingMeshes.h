#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "OverlappingMeshes.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AOverlappingMeshes : public AActor
{
	GENERATED_BODY()

public:
	AOverlappingMeshes();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USceneComponent> RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UFUNCTION()
	void HandleBoxComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex,
		bool				 bFromSweep,
		const FHitResult&	 SweepResult);

	UFUNCTION()
	void HandleBoxComponentEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex);

private:
	void PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp) const;
};