#include "IcicleTrap.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Icicle.h"

AIcicleTrap::AIcicleTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	CeilingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CeilingMesh"));
	CeilingMesh->SetupAttachment(SceneRoot);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(SceneRoot);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollider->SetupAttachment(SceneRoot);
}

void AIcicleTrap::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AIcicleTrap::OnOverlapBegin);

	SpawnIcicle();
}

void AIcicleTrap::SpawnIcicle()
{
	if (bIsActivated)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = FRotator::ZeroRotator;
	ActiveIcicle = GetWorld()->SpawnActor<AIcicle>(Icicle, SpawnLocation, SpawnRotation, SpawnParams);
	if (!ActiveIcicle)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn icicle in %s"), *GetName());
		return;
	}

	bIsActivated = true;
}

void AIcicleTrap::HandleTrapActivate()
{
	bIsActivated = false;
	ActiveIcicle->TurnPhysicsOn();

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &AIcicleTrap::HandleRespawn, RespawnDelay);
}

void AIcicleTrap::HandleRespawn()
{
	SpawnIcicle();
}

void AIcicleTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
		return;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!OtherCharacter)
		return;

	if (!bIsActivated)
		return;

	if (!ActiveIcicle)
		return;

	GetWorldTimerManager().SetTimer(TrapActivateTimer, this, &AIcicleTrap::HandleTrapActivate, TrapActivateDelay);
}
