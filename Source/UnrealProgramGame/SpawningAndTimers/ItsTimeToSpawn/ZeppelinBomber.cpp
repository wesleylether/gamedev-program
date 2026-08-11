#include "ZeppelinBomber.h"

#include "CannonBall.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"

AZeppelinBomber::AZeppelinBomber()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(SceneRoot);
}

void AZeppelinBomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SplineComponent)
		return;

	const FTransform Transform = SplineComponent->GetTransformAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
	const FTransform NewTransform = FTransform(Transform.GetRotation(), Transform.GetLocation(), GetActorScale3D());

	SetActorTransform(NewTransform);

	DistanceAlongSpline += MovementSpeed * DeltaTime;

	if (bShouldLoop)
	{
		if (DistanceAlongSpline > SplineComponent->GetSplineLength())
		{
			DistanceAlongSpline = 0.0f;
		}
	}
}

void AZeppelinBomber::BeginPlay()
{
	Super::BeginPlay();

	if (SplineActor)
	{
		SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();
	}

	if (!Bomb)
		return;

	GetWorldTimerManager().SetTimer(BombSpawnTimer, this, &AZeppelinBomber::SpawnBomb, BombSpawnInterval, true);
}

void AZeppelinBomber::SpawnBomb()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	ACannonBall* SpawnedBomb = GetWorld()->SpawnActor<ACannonBall>(Bomb, SpawnLocation, SpawnRotation, SpawnParams);
	if (!SpawnedBomb)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn bomb in %s"), *GetName());
	}
}
