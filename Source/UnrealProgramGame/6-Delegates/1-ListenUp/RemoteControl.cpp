#include "RemoteControl.h"

void ARemoteControl::BeginPlay()
{
	Super::BeginPlay();

	if (Target)
	{
		Message(FString::Printf(TEXT("Target name is: %s"), *Target->GetName()), -1, 5.0f);
	}
}
