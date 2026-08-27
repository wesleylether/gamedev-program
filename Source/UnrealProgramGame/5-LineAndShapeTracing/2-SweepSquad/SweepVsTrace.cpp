
#include "SweepVsTrace.h"

#include "Enum/EScreenMessageKeys.h"

ASweepVsTrace::ASweepVsTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASweepVsTrace::BeginPlay()
{
	Super::BeginPlay();
}

void ASweepVsTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * SweepDistance;

	FHitResult SweepHitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(50.0f);
	const bool bSweepHit = GetWorld()->SweepSingleByChannel(SweepHitResult, GetActorLocation(), TraceEnd, FQuat::Identity, ECC_Visibility, CollisionShape, CollisionParams);

	FHitResult LineHitResult;
	const bool bLineHit = GetWorld()->LineTraceSingleByChannel(LineHitResult, GetActorLocation(), TraceEnd, ECC_Visibility, CollisionParams);

	if (bSweepHit)
	{
		DrawDebugSphere(GetWorld(), SweepHitResult.Location, 50.0f, 12, FColor::Red, false, 0.0f);
		DrawDebugSphere(GetWorld(), SweepHitResult.ImpactPoint, 5.0f, 12, FColor::Cyan, false, 0.0f);

		Message(FString::Printf(TEXT("Sweep Hit: %s"), *SweepHitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::SweepHit), 0.0f);
	}

	FColor LineColor = FColor::Green;
	if (bLineHit)
	{
		LineColor = FColor::Red;

		Message(FString::Printf(TEXT("Line Hit: %s"), *LineHitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::LineHit), 0.0f);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.0f, 12, FColor::Yellow, false, 0.0f);
	DrawDebugSphere(GetWorld(), TraceEnd, 50.0f, 12, FColor::Yellow, false, 0.0f);
	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
