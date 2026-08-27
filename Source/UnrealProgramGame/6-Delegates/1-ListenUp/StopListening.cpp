
#include "StopListening.h"

#include "Components/BoxComponent.h"

AStopListening::AStopListening()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetLineThickness(1.0f);
	Box->SetHiddenInGame(false);
	SetRootComponent(Box);
}

void AStopListening::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AStopListening::OnOverlapBegin);
	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AStopListening::OnOverlapBegin);
	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AStopListening::OnOverlapBegin);
}

void AStopListening::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Count >= 3)
	{
		Box->OnComponentBeginOverlap.RemoveDynamic(this, &AStopListening::OnOverlapBegin);
		Message(FString::Printf(TEXT("I Have seen enough!")));

		return;
	}

	Count++;

	Message(FString::Printf(TEXT("I have seen %s %d time(s)!"), *OtherActor->GetName(), Count));
}
