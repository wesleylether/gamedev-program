#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ActivatedPlatform.generated.h"

class ATargetPoint;

UCLASS()
class UNREALPROGRAMGAME_API AActivatedPlatform : public AActor
{
	GENERATED_BODY()

public:
	AActivatedPlatform();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> PlatformMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATargetPoint> TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 100.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	bool	bIsMoving = false;
	FVector BeginLocation;
	FVector EndLocation;
	FVector Destination;
};