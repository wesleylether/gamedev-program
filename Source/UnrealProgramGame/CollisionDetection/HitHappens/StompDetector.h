#pragma once

#include "CoreMinimal.h"
#include "TransformsAndMovement/Base/BaseMovementActor.h"

#include "StompDetector.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AStompDetector : public ABaseMovementActor
{
	GENERATED_BODY()

public:
	AStompDetector();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Happends")
	float MinStompZNormal = 0.5f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void ApplyRandomColor();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
};