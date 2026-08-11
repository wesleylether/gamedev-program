#include "TrapTrigger.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "SpawningAndTimers/Base/BaseSpawnObject.h"
#include "UnrealProgramGameCharacter.h"

ATrapTrigger::ATrapTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TrapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrapBox"));
	TrapBox->SetupAttachment(SceneRoot);

	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
	TrapMesh->SetupAttachment(SceneRoot);

	SpawnTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	SpawnTarget->SetupAttachment(SceneRoot);
}

void ATrapTrigger::BeginPlay()
{
	Super::BeginPlay();

	TrapBox->OnComponentBeginOverlap.AddDynamic(this, &ATrapTrigger::OnBoxOverlap);
}

void ATrapTrigger::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggerOnce && bHasTriggered)
		return;

	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!IsValid(Character))
		return;

	if (!SpawnClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn class is not set in actor: %s"), *GetName())
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABaseSpawnObject* SObject = GetWorld()->SpawnActor<ABaseSpawnObject>(SpawnClass, SpawnTarget->GetComponentLocation(), SpawnTarget->GetComponentRotation(), SpawnParams);

	if (!SObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn object: %s in actor: %s"), *SpawnClass->GetName(), *GetName());
		return;
	}

	if (SObject)
	{
		SObject->SetActorScale3D(FVector(3.0f));
		SObject->GetMesh()->GetBodyInstance()->SetMassOverride(400.0f);
		SObject->SetLifeSpan(10.0f);
	}

	if (bTriggerOnce)
		bHasTriggered = true;
}
