#include "Icicle.h"

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
