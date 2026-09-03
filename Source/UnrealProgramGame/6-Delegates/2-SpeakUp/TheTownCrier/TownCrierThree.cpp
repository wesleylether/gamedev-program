#include "TownCrierThree.h"

#include "6-Delegates/2-SpeakUp/TheTownCrier.h"

ATownCrierThree::ATownCrierThree()
{
	Mesh->SetSimulatePhysics(true);
}

void ATownCrierThree::BeginPlay()
{
	Super::BeginPlay();

	if (!TownCrier)
		return;

	TownCrier->OnSpeakUp.AddUniqueDynamic(this, &ATownCrierThree::Jump);
}

void ATownCrierThree::Jump()
{
	Mesh->AddImpulse(FVector(0.0f, 0.0f, 500.0f), NAME_None, true);
}
