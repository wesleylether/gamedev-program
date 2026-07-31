#include "PhysicsHit.h"

APhysicsHit::APhysicsHit()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMassOverrideInKg(NAME_None, 20.0f, true);
	StaticMesh->SetCollisionProfileName("BlockAllDynamic");
	StaticMesh->SetNotifyRigidBodyCollision(true);
}

void APhysicsHit::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	StaticMesh->OnComponentHit.AddDynamic(this, &APhysicsHit::OnHit);
}

void APhysicsHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitImpulse = NormalImpulse.Size();
	if (HitImpulse > 100000.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("HARD HIT!!!: %f"), HitImpulse);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("Soft hit...: %f"), HitImpulse);
	}
}
