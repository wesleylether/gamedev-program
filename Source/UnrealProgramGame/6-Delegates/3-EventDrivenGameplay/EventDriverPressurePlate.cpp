
#include "EventDriverPressurePlate.h"

#include "Components/BoxComponent.h"

AEventDriverPressurePlate::AEventDriverPressurePlate()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	Mesh->SetGenerateOverlapEvents(false);

	PrimaryActorTick.bCanEverTick = true;
}

void AEventDriverPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh || !Mesh->GetStaticMesh())
		return;

	const FBox MeshBoundingBox = Mesh->GetStaticMesh()->GetBoundingBox();
	const FVector MeshScale = Mesh->GetRelativeScale3D();
	const FVector MeshSize = MeshBoundingBox.GetSize() * MeshScale;
	const FVector MeshExtent = MeshSize * 0.5f;

	Box->SetBoxExtent(MeshExtent);
	Box->SetRelativeLocation(FVector(0.0f, 0.0f, MeshExtent.Z + MeshSize.Z));

	StartLocation = GetActorLocation();
	EndLocation = StartLocation - FVector(0.0f, 0.0f, MeshSize.Z - 1.0f);
	Destination = StartLocation;

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEventDriverPressurePlate::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddUniqueDynamic(this, &AEventDriverPressurePlate::OnOverlapEnd);
}

void AEventDriverPressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bActivated)
		return;

	bActivated = true;
	Destination = EndLocation;
	OnPressurePlatePressed.Broadcast();
}

void AEventDriverPressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bActivated)
		return;

	bActivated = false;
	Destination = StartLocation;
	OnPressurePlateReleased.Broadcast();
}

void AEventDriverPressurePlate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector CurrentLocation = GetActorLocation();

	if (CurrentLocation.Equals(Destination, 0.01f))
		return;

	const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), Destination, DeltaSeconds, 5.0f);
	SetActorLocation(NewLocation);
}
