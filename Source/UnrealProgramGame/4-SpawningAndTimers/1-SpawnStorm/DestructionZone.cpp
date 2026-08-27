
#include "DestructionZone.h"

#include "Components/BoxComponent.h"

ADestructionZone::ADestructionZone()
{
	DestructionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DestructionBox"));
	SetRootComponent(DestructionBox);
}

void ADestructionZone::BeginPlay()
{
	Super::BeginPlay();

	DestructionBox->OnComponentBeginOverlap.AddDynamic(this, &ADestructionZone::OnOverlapBegin);
}

void ADestructionZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && OtherActor != this)
	{
		OtherActor->Destroy();

		Log(FString::Printf(TEXT("Actor: %s destroyed"), *OtherActor->GetName()));
	}
}
