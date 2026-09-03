
#include "ZoneWatcher.h"

void AZoneWatcher::BeginPlay()
{
	Super::BeginPlay();

	if (Target)
	{
		Target->OnActorBeginOverlap.AddDynamic(this, &AZoneWatcher::OnTargetOverlap);
		Target->OnActorEndOverlap.AddDynamic(this, &AZoneWatcher::OnTargetEndOverlap);
	}
}

void AZoneWatcher::OnTargetOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Log(FString::Printf(TEXT("Target Overlap OtherActor: %s, Overlapped: %s"), *OtherActor->GetName(), *OverlappedActor->GetName()));
}

void AZoneWatcher::OnTargetEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Log(FString::Printf(TEXT("Target End Overlap OtherActor: %s, Overlapped: %s"), *OtherActor->GetName(), *OverlappedActor->GetName()));
}
