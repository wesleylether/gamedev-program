#include "HitEventHappens.h"

void AHitEventHappens::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	Mesh->OnComponentHit.AddDynamic(this, &AHitEventHappens::OnHit);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AHitEventHappens::OnOverlapBegin);
}

void AHitEventHappens::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Log(FString::Printf(TEXT("Something hit me! OtherActor: %s, OtherComp: %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp)));
}

void AHitEventHappens::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Log(FString::Printf(TEXT("Something overlapped me! OtherActor: %s, OtherComp: %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp)));
}
