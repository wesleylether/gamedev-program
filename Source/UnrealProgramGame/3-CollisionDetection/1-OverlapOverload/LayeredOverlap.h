#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "LayeredOverlap.generated.h"

class USphereComponent;

UCLASS()
class UNREALPROGRAMGAME_API ALayeredOverlap : public ABaseActor
{
	GENERATED_BODY()

public:
	ALayeredOverlap();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USphereComponent> InnerSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Detection")
	TObjectPtr<USphereComponent> OuterSphere;

	UFUNCTION()
	virtual void HandleSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};