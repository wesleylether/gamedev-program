#include "TheTownCrier.h"

ATheTownCrier::ATheTownCrier()
{
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ATheTownCrier::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATheTownCrier::OnOverlapBegin);
}

void ATheTownCrier::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OnSpeakUp.IsBound())
		return;

	OnSpeakUp.Broadcast();
}
