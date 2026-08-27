#include "Cannon.h"

#include "CannonBall.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UnrealProgramGameCharacter.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = true;

	InRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InRangeSphere"));
	InRangeSphere->SetupAttachment(SceneRoot);
	InRangeSphere->SetSphereRadius(2500.0f);
	InRangeSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InRangeSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InRangeSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(SceneRoot);
}

void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bActivated)
		return;

	if (!TargetActor)
		return;

	const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
	const FRotator CurrentRotation = GetActorRotation();

	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookRotation, DeltaTime, CannonSpeed);
	SetActorRotation(NewRotation);
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	InRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ACannon::OnOverlapBegin);
	InRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ACannon::OnOverlapEnd);
}

void ACannon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
		return;

	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	TargetActor = Character;

	GetWorldTimerManager().SetTimer(ProjectileSpawnTimer, this, &ACannon::OnProjectileSpawnTimer, ProjectileInterval, true);

	bActivated = true;
}

void ACannon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this)
		return;

	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	TargetActor = nullptr;

	GetWorldTimerManager().ClearTimer(ProjectileSpawnTimer);

	bActivated = false;
}

void ACannon::OnProjectileSpawnTimer()
{
	if (!BulletToSpawn)
		return;

	FVector SpawnLocation = Muzzle->GetComponentLocation();
	FRotator SpawnRotation = Muzzle->GetComponentRotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor(BulletToSpawn, &SpawnLocation, &SpawnRotation, Params);
	if (!SpawnedActor)
	{
		Log(FString::Printf(TEXT("%s: Failed to spawn bullet actor!"), *GetName()));
		return;
	}

	if (ACannonBall* CannonBall = Cast<ACannonBall>(SpawnedActor))
	{
		CannonBall->LaunchCannonBall(Muzzle->GetForwardVector(), CannonStrength);
	}
	else
	{
		if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent()))
		{
			if (RootPrim->IsSimulatingPhysics())
			{
				RootPrim->AddImpulse(Muzzle->GetForwardVector() * CannonStrength, NAME_None, true);
			}
		}
	}

	if (CannonSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CannonSound, SpawnLocation);
	}
}