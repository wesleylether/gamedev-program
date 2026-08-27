
#include "FirstSweep.h"

#include "Enum/EScreenMessageKeys.h"

AFirstSweep::AFirstSweep()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFirstSweep::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstSweep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * SweepDistance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(50.0f);
	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), TraceEnd, FQuat::Identity, ECC_Visibility, CollisionShape, CollisionParams);

	FColor LineColor = FColor::Green;
	if (bHit)
	{
		LineColor = FColor::Red;

		DrawDebugSphere(GetWorld(), HitResult.Location, 50.0f, 12, FColor::Red, false, 0.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 12, FColor::Cyan, false, 0.0f);

		Message(FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::SweepHit), 0.0f);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.0f, 12, FColor::Yellow, false, 0.0f);
	DrawDebugSphere(GetWorld(), TraceEnd, 50.0f, 12, FColor::Yellow, false, 0.0f);
	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
