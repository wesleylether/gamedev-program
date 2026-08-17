
#include "SolidMover.h"

ASolidMover::ASolidMover()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ASolidMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Log(FString::Printf(TEXT("Moving at speed: %f"), MovementSpeed));

	FVector Motion = GetActorForwardVector() * MovementSpeed * DeltaTime;

	if (!bForward)
		Motion *= -1.0f;

	FHitResult HitResult;
	AddActorLocalOffset(Motion, true, &HitResult);

	if (AActor* Actor = HitResult.GetActor())
	{
		Log(FString::Printf(TEXT("Hit actor: %s"), *Actor->GetName()));
	}

	if (HitResult.bBlockingHit)
	{
		bForward = !bForward;
	}
}
