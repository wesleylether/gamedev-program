#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "SentryEye.generated.h"

class USphereComponent;

UCLASS()
class UNREALPROGRAMGAME_API ASentryEye : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ASentryEye();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> VisibilitySphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VisibilitySphereRadius = 1000.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	UPROPERTY()
	TObjectPtr<APawn> Target;

	bool bActivated = false;
};