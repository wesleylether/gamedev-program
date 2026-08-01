#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BreakableDoor.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ABreakableDoor : public AActor
{
	GENERATED_BODY()

public:
	ABreakableDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BreakLimit = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BreakForce = 1000.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	bool bIsBroken = false;
};