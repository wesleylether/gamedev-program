
#include "OneToMany.h"

#include "Components/BoxComponent.h"

AOneToMany::AOneToMany()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetLineThickness(1.0f);
	Box->SetHiddenInGame(false);
	Box->SetupAttachment(GetRootComponent());

	bDebug = true;
}

void AOneToMany::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AOneToMany::OnOverlapBeginOne);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AOneToMany::OnOverlapBeginTwo);
}

void AOneToMany::OnOverlapBeginOne(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Log(FString::Printf(TEXT("OnOverlapBeginOne")));
}

void AOneToMany::OnOverlapBeginTwo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Log(FString::Printf(TEXT("OnOverlapBeginTwo")));
}
