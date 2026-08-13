#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "CoinPickup.generated.h"

class UNiagaraSystem;
class USceneComponent;
class USoundBase;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class UNREALPROGRAMGAME_API ACoinPickup : public ABaseActor
{
	GENERATED_BODY()

public:
	ACoinPickup();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin|Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin|Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Effects")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Effects")
	TObjectPtr<UNiagaraSystem> PickupNiagaraEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|IdleAnimation", meta = (ClampMin = "0.0"))
	float IdleBobAmplitude = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|IdleAnimation", meta = (ClampMin = "0.0"))
	float IdleBobFrequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|IdleAnimation", meta = (ClampMin = "0.0"))
	float IdleRotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Animation", meta = (ClampMin = "0.01"))
	float PickupAnimationDuration = 0.45f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Animation", meta = (ClampMin = "0.0"))
	float PickupDipDistance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Animation", meta = (ClampMin = "0.0"))
	float PickupRiseHeight = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin|Pickup|Animation", meta = (ClampMin = "0.0"))
	float PickupBackEaseStrength = 1.70158f;

	UFUNCTION()
	void HandleSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void UpdateIdleAnimation(float DeltaTime);
	void UpdatePickupAnimation(float DeltaTime);
	static float EaseOutBack(float Alpha, float Overshoot);

	FVector InitialActorLocation = FVector::ZeroVector;
	float PickupAnimationElapsedTime = 0.0f;
	bool bIsPickupInProgress = false;
};