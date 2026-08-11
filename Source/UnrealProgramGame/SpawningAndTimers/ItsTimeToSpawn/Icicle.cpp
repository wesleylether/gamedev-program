#include "Icicle.h"

AIcicle::AIcicle()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AIcicle::TurnPhysicsOn()
{
	Mesh->SetSimulatePhysics(true);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AIcicle::OnTimerTimeout, LifeSpan);
}

void AIcicle::OnTimerTimeout()
{
	Destroy();
}
