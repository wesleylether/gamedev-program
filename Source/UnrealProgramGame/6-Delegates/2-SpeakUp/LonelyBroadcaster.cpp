
#include "LonelyBroadcaster.h"

#include "Components/BoxComponent.h"

ALonelyBroadcaster::ALonelyBroadcaster()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetLineThickness(1.0f);
	Box->SetHiddenInGame(false);
	SetRootComponent(Box);
}

void ALonelyBroadcaster::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ALonelyBroadcaster::OnOverlapBegin);
}

void ALonelyBroadcaster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnLonelyBroadcast.Broadcast();

	if (!OnLonelyBroadcast.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnLonelyBroadcast is not bound"));
	}
}
