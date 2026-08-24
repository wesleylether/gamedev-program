
#include "ObjectTypeTrace.h"

AObjectTypeTrace::AObjectTypeTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObjectTypeTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * TraceDistance;

	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	// CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), TraceEnd, CollisionObjectQueryParams);

	FColor LineColor = FColor::Red;
	if (bHit)
	{
		LineColor = FColor::Green;

		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
	}
	else
	{
		AddActorWorldOffset(GetActorForwardVector() * MoveSpeed * DeltaTime);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
}
