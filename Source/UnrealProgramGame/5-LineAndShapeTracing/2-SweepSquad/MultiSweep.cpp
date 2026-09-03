#include "MultiSweep.h"

#include "Enum/EScreenMessageKeys.h"

AMultiSweep::AMultiSweep()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMultiSweep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + TraceLength * GetActorForwardVector();

	TArray<FHitResult> HitResult;
	FCollisionShape Shape = FCollisionShape::MakeSphere(50.0f);
	bool bHit = GetWorld()->SweepMultiByChannel(HitResult, GetActorLocation(), TraceEnd, FQuat::Identity, ECC_Visibility, Shape);

	if (bHit)
	{
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

				DrawDebugSphere(GetWorld(), HitResult[i].ImpactPoint, 5.0f, 10, FColor::Cyan, false, 0.0f, 0, 1.0f);
				DrawDebugSphere(GetWorld(), HitResult[i].Location, 50.0f, 10, FColor::Red, false, 0.0f, 0, 1.0f);
			}
		}

		Message(FString::Printf(TEXT("Hit %s"), *HitActorNames), static_cast<int32>(EScreenMessageKey::Sweep_Multi), 1.0f, FColor::Green);
	}
}
