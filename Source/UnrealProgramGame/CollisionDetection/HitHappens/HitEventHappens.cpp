#include "HitEventHappens.h"

AHitEventHappens::AHitEventHappens()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHitEventHappens::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	StaticMesh->OnComponentHit.AddDynamic(this, &AHitEventHappens::OnHit);
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AHitEventHappens::OnOverlapBegin);
}

void AHitEventHappens::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Something hit me! OtherActor: %s, OtherComp: %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp));
}

void AHitEventHappens::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Something overlapped me! OtherActor: %s, OtherComp: %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp));
}
