#include "SelectiveVision.h"

#include "Enum/EScreenMessageKeys.h"

ASelectiveVision::ASelectiveVision()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASelectiveVision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + TraceLength * GetActorForwardVector();

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), TraceEnd, ECC_Visibility);

	FColor LineColor = FColor::Red;
	if (bHit)
	{
		LineColor = FColor::Green;

		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
