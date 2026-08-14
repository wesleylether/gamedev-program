#include "PhysicsHit.h"

APhysicsHit::APhysicsHit()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetMassOverrideInKg(NAME_None, 20.0f, true);
	Mesh->SetCollisionProfileName("BlockAllDynamic");
	Mesh->SetNotifyRigidBodyCollision(true);
}

void APhysicsHit::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	Mesh->OnComponentHit.AddDynamic(this, &APhysicsHit::OnHit);
}

void APhysicsHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitImpulse = NormalImpulse.Size();
	if (HitImpulse > 100000.0f)
	{
		Log(FString::Printf(TEXT("HARD HIT!!!: %f"), HitImpulse));
	}
	else
	{
		Log(FString::Printf(TEXT("Soft hit...: %f"), HitImpulse));
	}
}
