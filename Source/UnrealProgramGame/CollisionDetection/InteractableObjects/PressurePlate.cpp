#include "PressurePlate.h"

#include "Components/BoxComponent.h"
#include "Enum/EScreenMessageKeys.h"

APressurePlate::APressurePlate()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	Mesh->SetupAttachment(BoxComponent);
	Mesh->SetGenerateOverlapEvents(false);
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = Mesh->GetRelativeLocation();
	if (CurrentLocation.Equals(Destination))
		return;

	float NewZ = FMath::FInterpTo(CurrentLocation.Z, Destination.Z, DeltaTime, 10.0f);
	Mesh->SetRelativeLocation(FVector(CurrentLocation.X, CurrentLocation.Y, NewZ));
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);

	StartLocation = Mesh->GetRelativeLocation();
	EndLocation = StartLocation - FVector(0.0f, 0.0f, Mesh->GetStaticMesh()->GetBounds().GetBox().GetSize().Z);
	Destination = StartLocation;
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Message(FString::Printf(TEXT("OnOverlapBegin")), static_cast<int32>(EScreenMessageKey::PressurePlate_Status), 3.0f, FColor::Purple);

	FString TagsString = TEXT("Tags: ");
	for (const FName& Tag : OtherActor->Tags)
	{
		TagsString += Tag.ToString() + TEXT(", ");
	}
	Message(TagsString, static_cast<int32>(EScreenMessageKey::PressurePlate_Tags), 3.0f, FColor::Cyan);

	if (!OtherActor->ActorHasTag("Player") && !OtherActor->ActorHasTag("PressurePlateActivator"))
		return;

	Message(FString::Printf(TEXT("Tags available")), static_cast<int32>(EScreenMessageKey::PressurePlate_Status), 3.0f, FColor::Purple);

	ActivationCount++;

	if (bIsActivated)
		return;

	bIsActivated = true;
	Destination = EndLocation;
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->ActorHasTag("Player") && !OtherActor->ActorHasTag("PressurePlateActivator"))
		return;

	ActivationCount--;

	if (ActivationCount > 0)
		return;

	bIsActivated = false;
	Destination = StartLocation;
}