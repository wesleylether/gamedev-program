
#include "Doorbell.h"

void ADoorbell::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADoorbell::OnOverlapBegin);
}

void ADoorbell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Log(FString::Printf(TEXT("%s: Ringing the doorbel"), *GetName()));
	OnDoorbellRung.Broadcast();
}
