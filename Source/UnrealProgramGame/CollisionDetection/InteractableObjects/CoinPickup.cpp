#include "CoinPickup.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

ACoinPickup::ACoinPickup()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootSceneComponent);
	SphereComponent->SetSphereRadius(150.0f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SphereComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PrimaryActorTick.bCanEverTick = true;
}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();

	InitialActorLocation = GetActorLocation();

	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::HandleSphereComponentBeginOverlap);
	}
}

void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MeshComponent)
		return;

	if (bIsPickupInProgress)
	{
		UpdatePickupAnimation(DeltaTime);
		return;
	}

	UpdateIdleAnimation(DeltaTime);
}

void ACoinPickup::HandleSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsPickupInProgress || !OtherActor || OtherActor == this)
	{
		return;
	}

	bIsPickupInProgress = true;
	PickupAnimationElapsedTime = 0.0f;

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}

	if (PickupNiagaraEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickupNiagaraEffect, GetActorLocation());
	}

	if (SphereComponent)
	{
		SphereComponent->SetGenerateOverlapEvents(false);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	SetActorEnableCollision(false);
}

void ACoinPickup::UpdateIdleAnimation(const float DeltaTime)
{
	if (!GetWorld())
		return;

	const float BobOffset = FMath::Sin(GetWorld()->GetTimeSeconds() * IdleBobFrequency) * IdleBobAmplitude;
	SetActorLocation(InitialActorLocation + FVector(0.0f, 0.0f, BobOffset));
	AddActorLocalRotation(FRotator(0.0f, IdleRotationSpeed * DeltaTime, 0.0f));
}

void ACoinPickup::UpdatePickupAnimation(const float DeltaTime)
{
	PickupAnimationElapsedTime += DeltaTime;

	const float		AnimationAlpha = FMath::Clamp(PickupAnimationElapsedTime / PickupAnimationDuration, 0.0f, 1.0f);
	constexpr float DownwardPhaseThreshold = 0.25f;

	float VerticalOffset = 0.0f;
	float ScaleValue = 1.0f;

	if (AnimationAlpha <= DownwardPhaseThreshold)
	{
		const float DownwardAlpha = AnimationAlpha / DownwardPhaseThreshold;
		const float DownwardEase = FMath::InterpEaseIn(0.0f, 1.0f, DownwardAlpha, 2.5f);
		VerticalOffset = FMath::Lerp(0.0f, -PickupDipDistance, DownwardEase);
	}
	else
	{
		const float UpwardAlpha = (AnimationAlpha - DownwardPhaseThreshold) / (1.0f - DownwardPhaseThreshold);
		const float UpwardEase = EaseOutBack(UpwardAlpha, PickupBackEaseStrength);
		VerticalOffset = FMath::Lerp(-PickupDipDistance, PickupRiseHeight, UpwardEase);

		const float ScaleAlpha = FMath::InterpEaseIn(0.0f, 1.0f, UpwardAlpha, 2.0f);
		ScaleValue = FMath::Lerp(1.0f, 0.0f, ScaleAlpha);
	}

	SetActorLocation(InitialActorLocation + FVector(0.0f, 0.0f, VerticalOffset));
	SetActorScale3D(FVector(FMath::Max(ScaleValue, 0.0f)));
	AddActorLocalRotation(FRotator(0.0f, IdleRotationSpeed * 10.0f * DeltaTime, 0.0f));

	if (AnimationAlpha >= 1.0f)
	{
		Destroy();
	}
}

float ACoinPickup::EaseOutBack(const float Alpha, const float Overshoot)
{
	const float InverseAlpha = Alpha - 1.0f;
	const float OvershootFactor = Overshoot + 1.0f;
	return 1.0f + OvershootFactor * FMath::Pow(InverseAlpha, 3.0f) + Overshoot * FMath::Pow(InverseAlpha, 2.0f);
}
