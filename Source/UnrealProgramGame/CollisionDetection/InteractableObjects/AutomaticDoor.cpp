#include "AutomaticDoor.h"

#include "Components/BoxComponent.h"

AAutomaticDoor::AAutomaticDoor()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	DoorCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollisionComponent"));
	DoorCollisionComponent->SetupAttachment(SceneRootComponent);
	DoorCollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	DoorCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DoorCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	DoorCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DoorCollisionComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneRootComponent);

	DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshComponent"));
	DoorMeshComponent->SetupAttachment(SceneRootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void AAutomaticDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorStartLocation = DoorMeshComponent->GetComponentLocation();
	DoorEndLocation = DoorStartLocation - FVector(0.0f, 0.0f, StaticMeshComponent->GetStaticMesh()->GetBounds().GetBox().GetSize().Z);
	DoorDestination = DoorStartLocation;

	DoorCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAutomaticDoor::OnOverlapBegin);
	DoorCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAutomaticDoor::OnOverlapEnd);
}

void AAutomaticDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsActivated)
		return;

	DoorDestination = DoorEndLocation;
	bIsActivated = true;
}

void AAutomaticDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsActivated)
		return;

	DoorDestination = DoorStartLocation;
	bIsActivated = false;
}

void AAutomaticDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = DoorMeshComponent->GetComponentLocation();
	if (CurrentLocation.Equals(DoorDestination))
		return;

	FVector NewLocation = FMath::VInterpTo(CurrentLocation, DoorDestination, DeltaTime, 10.0f);
	DoorMeshComponent->SetWorldLocation(NewLocation);
}
