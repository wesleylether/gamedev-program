#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "CannonBall.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
class URadialForceComponent;

UCLASS()
class UNREALPROGRAMGAME_API ACannonBall : public ABaseActor
{
	GENERATED_BODY()

public:
	ACannonBall();

	void LaunchCannonBall(const FVector& LaunchDirection, float LaunchStrength);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Visuals")
	TObjectPtr<UStaticMeshComponent> CannonBallMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Visuals")
	TObjectPtr<UNiagaraComponent> CannonBallEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Collision")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Explosion")
	TObjectPtr<URadialForceComponent> ExplosionForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Config")
	float CannonBallLifeTime = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosion")
	float CannonBallPower = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosion")
	float ExplosionRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosion")
	float ExplosionEffectLifetime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosion")
	bool bOnlyHitActors = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Explosion")
	TObjectPtr<UNiagaraComponent> CannonBallExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosion")
	TObjectPtr<USoundBase> ExplosionSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void Explode();

	UFUNCTION()
	void OnExplosionFinished();

private:
	FTimerHandle LifeTimerHandle;
	bool bHasExploded = false;
};