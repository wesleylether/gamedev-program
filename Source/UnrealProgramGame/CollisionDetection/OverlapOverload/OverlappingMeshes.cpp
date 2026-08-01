#include "OverlappingMeshes.h"

AOverlappingMeshes::AOverlappingMeshes()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->SetupAttachment(RootComp);

	PrimaryActorTick.bCanEverTick = false;
}

void AOverlappingMeshes::BeginPlay()
{
	Super::BeginPlay();

	if (!MeshComponent)
		return;

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AOverlappingMeshes::HandleBoxComponentBeginOverlap);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AOverlappingMeshes::HandleBoxComponentEndOverlap);
}

void AOverlappingMeshes::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintOverlapMessage(TEXT("Overlap Begin"), OtherActor, OtherComp);
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
		return;
}

void AOverlappingMeshes::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PrintOverlapMessage(TEXT("Overlap End"), OtherActor, OtherComp);
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
		return;
}

void AOverlappingMeshes::PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp) const
{
	const FString Message = FString::Printf(TEXT("%s: %s | %s"), *EventName, *GetNameSafe(OtherActor), *GetNameSafe(OtherComp));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Message);
}
