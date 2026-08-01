#include "PressurePlate.h"

#include "Components/BoxComponent.h"

APressurePlate::APressurePlate()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComp);
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	StaticMesh->SetupAttachment(BoxComponent);
	StaticMesh->SetGenerateOverlapEvents(false);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);

	StartLocation = StaticMesh->GetRelativeLocation();
	EndLocation = StartLocation - FVector(0.0f, 0.0f, StaticMesh->GetStaticMesh()->GetBounds().GetBox().GetSize().Z);
	Destination = StartLocation;
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(7, 3.0f, FColor::Purple, FString::Printf(TEXT("OnOverlapBegin")));

	FString TagsString = TEXT("Tags: ");
	for (const FName& Tag : OtherActor->Tags)
	{
		TagsString += Tag.ToString() + TEXT(", ");
	}
	GEngine->AddOnScreenDebugMessage(8, 3.0f, FColor::Cyan, TagsString);

	if (!OtherActor->ActorHasTag("Player") && !OtherActor->ActorHasTag("PressurePlateActivator"))
		return;

	GEngine->AddOnScreenDebugMessage(7, 3.0f, FColor::Purple, FString::Printf(TEXT("Tags available")));

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

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = StaticMesh->GetRelativeLocation();
	if (CurrentLocation.Equals(Destination))
		return;

	float NewZ = FMath::FInterpTo(CurrentLocation.Z, Destination.Z, DeltaTime, 10.0f);
	StaticMesh->SetRelativeLocation(FVector(CurrentLocation.X, CurrentLocation.Y, NewZ));
}
