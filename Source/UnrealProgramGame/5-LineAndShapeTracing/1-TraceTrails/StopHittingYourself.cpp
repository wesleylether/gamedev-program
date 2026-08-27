#include "StopHittingYourself.h"

#include "Enum/EScreenMessageKeys.h"

AStopHittingYourself::AStopHittingYourself()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStopHittingYourself::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + TraceLength * GetActorForwardVector();

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // this is done by default if no Params are provided. Then it used the FCollisionQueryParams::DefaultQueryParam
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), TraceEnd, ECC_Visibility, Params);

	FColor LineColor = FColor::Red;
	if (bHit)
	{
		LineColor = FColor::Green;

		Message(FString::Printf(TEXT("Hit %s"), *HitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::Trace_StopHittingYourself), 1.0f, LineColor);

		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
