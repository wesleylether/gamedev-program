
#include "EventDrivenDoor.h"

#include "EventDriverPressurePlate.h"

AEventDrivenDoor::AEventDrivenDoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void AEventDrivenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!Door || !Door->GetStaticMesh())
		return;

	const FBox DoorBoundingBox = Door->GetStaticMesh()->GetBoundingBox();
	const FVector DoorScale = Door->GetRelativeScale3D();
	const FVector DoorSize = DoorBoundingBox.GetSize() * DoorScale;

	DoorStartLocation = Door->GetComponentLocation();
	DoorEndLocation = DoorStartLocation - FVector(0.0f, 0.0f, DoorSize.Z - 3.0f);
	DoorDestination = DoorStartLocation;

	for (const auto& PressurePlate : PressurePlates)
	{
		PressurePlate->OnPressurePlatePressed.AddUniqueDynamic(this, &AEventDrivenDoor::OnPressurePlatePressed);
		PressurePlate->OnPressurePlateReleased.AddUniqueDynamic(this, &AEventDrivenDoor::OnPressurePlateReleased);
	}
}

void AEventDrivenDoor::OnPressurePlatePressed()
{
	DoorActivatedCount++;

	if (DoorActivatedCount == PressurePlates.Num())
	{
		OpenDoor();
	}
}

void AEventDrivenDoor::OnPressurePlateReleased()
{
	DoorActivatedCount--;

	if (DoorActivatedCount < PressurePlates.Num())
	{
		CloseDoor();
	}
}

void AEventDrivenDoor::OpenDoor()
{
	DoorDestination = DoorEndLocation;
}

void AEventDrivenDoor::CloseDoor()
{
	DoorDestination = DoorStartLocation;
}

void AEventDrivenDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector CurrentLocation = Door->GetComponentLocation();
	if (CurrentLocation.Equals(DoorDestination, 0.01f))
		return;

	const FVector NewLocation = FMath::VInterpTo(CurrentLocation, DoorDestination, DeltaTime, DoorSpeed);
	Door->SetWorldLocation(NewLocation);
}
