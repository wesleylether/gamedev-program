
#include "QuestDoor.h"

#include "EventSubsystems/QuestEventSubsystem.h"

AQuestDoor::AQuestDoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void AQuestDoor::BeginPlay()
{
	Super::BeginPlay();

	checkf(QuestTag.IsValid(), TEXT("QuestGiver: QuestTag is not set! This is mandatory."));

	QuestEventSubsystem = GetWorld()->GetSubsystem<UQuestEventSubsystem>();
	checkf(QuestEventSubsystem, TEXT("QuestGiver: QuestEventSubsystem is not found!"));

	QuestEventSubsystem->OnQuestStateChanged.AddUniqueDynamic(this, &AQuestDoor::HandleQuestEvent);

	if (!Door || !Door->GetStaticMesh())
		return;

	const FBox DoorBoundingBox = Door->GetStaticMesh()->GetBoundingBox();
	const FVector DoorScale = Door->GetRelativeScale3D();
	const FVector DoorSize = DoorBoundingBox.GetSize() * DoorScale;

	DoorStartLocation = Door->GetComponentLocation();
	DoorEndLocation = DoorStartLocation - FVector(0.0f, 0.0f, DoorSize.Z - 3.0f);
	DoorDestination = DoorStartLocation;
}

void AQuestDoor::HandleQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator)
{
	if (Tag != QuestTag)
		return;

	switch (State)
	{
		case EQuestTriggerState::Started:
			DoorDestination = DoorEndLocation;
			break;
		default:
			DoorDestination = DoorStartLocation;
			break;
	}
}

void AQuestDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector CurrentLocation = Door->GetComponentLocation();
	if (CurrentLocation.Equals(DoorDestination, 0.01f))
		return;

	const FVector NewLocation = FMath::VInterpTo(CurrentLocation, DoorDestination, DeltaTime, DoorSpeed);
	Door->SetWorldLocation(NewLocation);
}
