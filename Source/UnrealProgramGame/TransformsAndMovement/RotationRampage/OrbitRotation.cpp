#include "OrbitRotation.h"

AOrbitRotation::AOrbitRotation()
{
	SecondStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Static Mesh"));
	SecondStaticMesh->SetupAttachment(GetRootComponent());
}

void AOrbitRotation::BeginPlay()
{
	Super::BeginPlay();
}

void AOrbitRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, MovementSpeed * DeltaTime, 0.0f));
}
