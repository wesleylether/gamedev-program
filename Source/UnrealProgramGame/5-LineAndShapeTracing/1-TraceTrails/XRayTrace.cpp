#include "XRayTrace.h"

#include "Enum/EScreenMessageKeys.h"

AXRayTrace::AXRayTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXRayTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + TraceLength * GetActorForwardVector();

	TArray<FHitResult> HitResult;
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResult, GetActorLocation(), TraceEnd, ECC_Visibility);

	FColor LineColor = FColor::Red;
	if (bHit)
	{
		LineColor = FColor::Green;

		FString HitActorNames;
		for (int32 i = 0; i < HitResult.Num(); ++i)
		{
			if (HitResult[i].GetActor())
			{
				if (i > 0)
				{
					HitActorNames += TEXT(", ");
				}
				HitActorNames += HitResult[i].GetActor()->GetName();

				DrawDebugSphere(GetWorld(), HitResult[i].Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
			}
		}

		Message(FString::Printf(TEXT("Hit %s"), *HitActorNames), static_cast<int32>(EScreenMessageKey::Trace_XRayTrace), 1.0f, LineColor);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}