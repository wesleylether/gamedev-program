#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "Cannon.generated.h"

class UNiagaraSystem;
class UArrowComponent;
class USphereComponent;

UCLASS()
class UNREALPROGRAMGAME_API ACannon : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ACannon();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Collision")
	TObjectPtr<USphereComponent> InRangeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Muzzle")
	TObjectPtr<UArrowComponent> Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Sound")
	TObjectPtr<USoundBase> CannonSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Movement")
	float CannonSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Projectile")
	TSubclassOf<AActor> BulletToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Projectile")
	float ProjectileInterval = 9.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon|Projectile")
	float CannonStrength = 3000.0f;

private:
	bool bActivated = false;
	FTimerHandle ProjectileSpawnTimer;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> TargetActor = nullptr;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnProjectileSpawnTimer();
};