
#include "Rangefinder.h"

#include "Enum/EScreenMessageKeys.h"

ARangefinder::ARangefinder()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARangefinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * MaxRange;

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), TraceEnd, ECC_Visibility);

	if (bHit)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), HitResult.Location, FColor::Green, false, 0.0f, 0, 1.0f);

		const float Distance = FVector::Distance(GetActorLocation(), HitResult.Location);
		Message(FString::Printf(TEXT("Distance: %f"), Distance), static_cast<int32>(EScreenMessageKey::Trace_Distance), DeltaTime);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, FColor::Red, false, 0.0f, 0, 1.0f);
	}
}
