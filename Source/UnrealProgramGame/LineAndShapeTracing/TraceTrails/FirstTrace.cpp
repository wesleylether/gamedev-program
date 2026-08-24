#include "FirstTrace.h"

#include "Enum/EScreenMessageKeys.h"

AFirstTrace::AFirstTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFirstTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + TraceLength * GetActorForwardVector();

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), TraceEnd, ECC_Visibility);

	FColor LineColor = FColor::Red;
	if (bHit)
	{
		LineColor = FColor::Green;

		Message(FString::Printf(TEXT("Hit %s"), *HitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::Trace_FirstTrace), 1.0f, LineColor);

		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
