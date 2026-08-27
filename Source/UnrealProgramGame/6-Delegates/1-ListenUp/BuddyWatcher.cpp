
#include "BuddyWatcher.h"

void ABuddyWatcher::BeginPlay()
{
	Super::BeginPlay();

	if (Buddy)
	{
		Buddy->OnDestroyed.AddDynamic(this, &ABuddyWatcher::OnDestroyed);
	}
}

void ABuddyWatcher::OnDestroyed(AActor* DestroyedActor)
{
	Log(FString::Printf(TEXT("Buddy destroyed! %s"), *DestroyedActor->GetName()));
}
