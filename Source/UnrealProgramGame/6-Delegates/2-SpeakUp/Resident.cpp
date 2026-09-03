
#include "Resident.h"

#include "Doorbell.h"

void AResident::BeginPlay()
{
	Super::BeginPlay();

	if (!Doorbell)
		return;

	Doorbell->OnDoorbellRung.AddDynamic(this, &AResident::OnDoorbellRung);
}

void AResident::OnDoorbellRung()
{
	Log(FString::Printf(TEXT("%s! I am coming"), *GetName()));
}
