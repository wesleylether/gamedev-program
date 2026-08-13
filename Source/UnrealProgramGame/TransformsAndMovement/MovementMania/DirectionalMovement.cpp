#include "DirectionalMovement.h"

ADirectionalMovement::ADirectionalMovement()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void ADirectionalMovement::BeginPlay()
{
	Super::BeginPlay();
}

void ADirectionalMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Direction = ArrowComponent->GetForwardVector();
	const FVector CurrentLocation = GetActorLocation();

	SetActorLocation(CurrentLocation + Direction * MovementSpeed * DeltaTime);
}
