
#include "SolidMover.h"

#include "Components/ArrowComponent.h"

ASolidMover::ASolidMover()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(GetRootComponent());
}

void ASolidMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Motion = Direction->GetForwardVector() * MovementSpeed * DeltaTime;

	FHitResult HitResult;
	AddActorLocalOffset(Motion, true, &HitResult);

	if (const AActor* Actor = HitResult.GetActor())
	{
		Log(FString::Printf(TEXT("Hit actor: %s"), *Actor->GetName()));
	}

	if (HitResult.bBlockingHit)
	{
		const FVector OppsiteDirection = Direction->GetForwardVector() * -1.0f;
		Direction->SetRelativeRotation(OppsiteDirection.Rotation());
	}
}
