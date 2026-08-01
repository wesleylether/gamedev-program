#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LayeredOverlap.generated.h"

class USphereComponent;

UCLASS()
class UNREALPROGRAMGAME_API ALayeredOverlap : public AActor
{
	GENERATED_BODY()

public:
	ALayeredOverlap();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USceneComponent> RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USphereComponent> InnerSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USphereComponent> OuterSphereComponent;

	UFUNCTION()
	virtual void HandleSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex,
		bool				 bFromSweep,
		const FHitResult&	 SweepResult);

	UFUNCTION()
	virtual void HandleSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor*				 OtherActor,
		UPrimitiveComponent* OtherComp,
		int32				 OtherBodyIndex);
};