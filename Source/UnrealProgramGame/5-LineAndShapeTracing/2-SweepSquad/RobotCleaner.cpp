
#include "RobotCleaner.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "WorldCollision.h"

ARobotCleaner::ARobotCleaner()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ARobotCleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector ForwardVector = GetActorForwardVector();
	const FVector DeltaLocation = ForwardVector * Speed * DeltaTime;

	FHitResult SweepHitResult;
	AddActorWorldOffset(DeltaLocation, true, &SweepHitResult);

	if (!SweepHitResult.bBlockingHit)
		return;

	TArray<FVector> AvailableDirections;

	const FVector LeftDir = -GetActorRightVector();
	const FVector RightDir = GetActorRightVector();
	const FVector BackDir = -GetActorForwardVector();

	const TArray DirectionsToCheck = { LeftDir, RightDir, BackDir };

	float SweepRadius = 50.0f;
	if (Mesh)
	{
		FVector Min, Max;
		Mesh->GetLocalBounds(Min, Max);
		SweepRadius = FMath::Max(Max.X - Min.X, Max.Y - Min.Y) * 0.5f;
		if (SweepRadius <= 0.0f)
		{
			SweepRadius = 50.0f;
		}
	}

	const FCollisionShape SweepShape = FCollisionShape::MakeSphere(SweepRadius);
	const float SweepDistance = 100.0f;

	for (const FVector& Dir : DirectionsToCheck)
	{
		FHitResult Hit;
		const FVector VerticalOffset = FVector(0.f, 0.f, SweepRadius + 2.0f);
		const FVector Start = GetActorLocation() + VerticalOffset;
		const FVector End = Start + Dir * SweepDistance;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		const bool bIsBlocked = GetWorld()->SweepSingleByChannel(
			Hit,
			Start,
			End,
			FQuat::Identity,
			ECC_Visibility,
			SweepShape,
			Params);

		if (!bIsBlocked)
		{
			AvailableDirections.Add(Dir);
		}
		else
		{
			Log(FString::Printf(TEXT("Blocked direction: %s"), *Dir.ToString()));
		}
	}

	if (AvailableDirections.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, AvailableDirections.Num() - 1);
		const FVector SelectedDir = AvailableDirections[RandomIndex];

		const FRotator NewRotation = SelectedDir.Rotation();
		SetActorRotation(NewRotation);
	}
}
