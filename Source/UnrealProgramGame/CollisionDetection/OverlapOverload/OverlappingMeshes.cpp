#include "OverlappingMeshes.h"

void AOverlappingMeshes::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOverlappingMeshes::HandleBoxComponentBeginOverlap);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AOverlappingMeshes::HandleBoxComponentEndOverlap);
}

void AOverlappingMeshes::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
		return;

	PrintOverlapMessage(TEXT("Overlap Begin"), OtherActor, OtherComp);
}

void AOverlappingMeshes::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
		return;

	PrintOverlapMessage(TEXT("Overlap End"), OtherActor, OtherComp);
}

void AOverlappingMeshes::PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp) const
{
	Message(FString::Printf(TEXT("%s: %s | %s"), *EventName, *GetNameSafe(OtherActor), *GetNameSafe(OtherComp)), -1, 2.0f, FColor::Green);
}
