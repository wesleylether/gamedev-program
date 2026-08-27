
#include "ActivatedPlatform.h"

#include "Engine/TargetPoint.h"

AActivatedPlatform::AActivatedPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActivatedPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsMoving)
		return;

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, Destination, DeltaTime, MoveSpeed);
	SetActorLocation(NewLocation);

	if (NewLocation.Equals(Destination) || NewLocation.Equals(EndLocation))
	{
		bIsMoving = false;
	}
}

void AActivatedPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (!TargetPoint || !Mesh)
		return;

	BeginLocation = GetActorLocation();
	EndLocation = TargetPoint->GetActorLocation();
	Destination = BeginLocation;

	Mesh->OnComponentHit.AddDynamic(this, &AActivatedPlatform::OnHit);
}

void AActivatedPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsMoving)
		return;

	if (Destination.Equals(EndLocation))
	{
		Destination = BeginLocation;
	}
	else if (Destination.Equals(BeginLocation))
	{
		Destination = EndLocation;
	}

	bIsMoving = true;
}
