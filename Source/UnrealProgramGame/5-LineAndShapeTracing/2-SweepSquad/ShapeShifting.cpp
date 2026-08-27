
#include "ShapeShifting.h"

#include "Components/ArrowComponent.h"
#include "Enum/EScreenMessageKeys.h"

AShapeShifting::AShapeShifting()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void AShapeShifting::BeginPlay()
{
	Super::BeginPlay();
}

void AShapeShifting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * SweepDistance;
	const FQuat ArrowRotation = ArrowComponent->GetComponentQuat();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionShape CollisionShape;
	switch (ShapeType)
	{
		case Box:
			CollisionShape = FCollisionShape::MakeBox(BoxExtend);
			break;
		case Capsule:
			CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
			break;
		default:
		case Sphere:
			CollisionShape = FCollisionShape::MakeSphere(SphereRadius);
			break;
	}

	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), TraceEnd, ArrowRotation, ECC_Visibility, CollisionShape, CollisionParams);

	if (bHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 12, FColor::Cyan, false, 0.0f);
		switch (ShapeType)
		{
			case Box:
				DrawDebugBox(GetWorld(), HitResult.Location, BoxExtend, ArrowRotation, FColor::Red, false, 0.0f);
				break;
			case Capsule:
				DrawDebugCapsule(GetWorld(), HitResult.Location, CapsuleRadius, CapsuleHalfHeight, ArrowRotation, FColor::Red, false, 0.0f);
				break;
			default:
			case Sphere:
				DrawDebugSphere(GetWorld(), HitResult.Location, SphereRadius, 12, FColor::Red, false, 0.0f);
				break;
		}

		Message(FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::SweepHit), 0.0f);
	}

	switch (ShapeType)
	{
		case Box:
			DrawDebugBox(GetWorld(), GetActorLocation(), BoxExtend, ArrowRotation, FColor::Yellow, false, 0.0f);
			DrawDebugBox(GetWorld(), TraceEnd, BoxExtend, ArrowRotation, FColor::Yellow, false, 0.0f);
			break;
		case Capsule:
			DrawDebugCapsule(GetWorld(), GetActorLocation(), CapsuleRadius, CapsuleHalfHeight, ArrowRotation, FColor::Yellow, false, 0.0f);
			DrawDebugCapsule(GetWorld(), TraceEnd, CapsuleRadius, CapsuleHalfHeight, ArrowRotation, FColor::Yellow, false, 0.0f);
			break;
		default:
		case Sphere:
			DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 12, FColor::Yellow, false, 0.0f);
			DrawDebugSphere(GetWorld(), TraceEnd, SphereRadius, 12, FColor::Yellow, false, 0.0f);
			break;
	}
}
