#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "BreakableDoor.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API ABreakableDoor : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ABreakableDoor();

protected:
	virtual void BeginPlay() override;

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