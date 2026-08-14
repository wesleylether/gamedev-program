#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "ActivatedPlatform.generated.h"

class ATargetPoint;

UCLASS()
class UNREALPROGRAMGAME_API AActivatedPlatform : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AActivatedPlatform();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATargetPoint> TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 100.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	bool bIsMoving = false;
	FVector BeginLocation;
	FVector EndLocation;
	FVector Destination;
};