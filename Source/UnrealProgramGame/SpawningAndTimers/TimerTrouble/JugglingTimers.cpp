#include "JugglingTimers.h"

#include "Engine/StaticMeshActor.h"

AJugglingTimers::AJugglingTimers()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AJugglingTimers::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	GetWorldTimerManager().SetTimer(ColorTimerHandle, this, &AJugglingTimers::ChangeColor, ColorTimerLength, true);
	GetWorldTimerManager().SetTimer(LogTimerHandle, this, &AJugglingTimers::LogMessage, LogTimerLength, true);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AJugglingTimers::SpawnActor, SpawnTimerLength, true);
}

void AJugglingTimers::ChangeColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}

void AJugglingTimers::LogMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("TimerHandled in %s"), *GetName());
}

void AJugglingTimers::SpawnActor()
{
	if (!IsValid(SpawnedMesh))
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	const FVector  SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = FRotator(FMath::FRandRange(0.0f, 360.0f));

	if (AStaticMeshActor* StaticMeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(SpawnLocation, SpawnRotation, SpawnParams))
	{
		StaticMeshActor->SetMobility(EComponentMobility::Movable);
		StaticMeshActor->GetStaticMeshComponent()->SetSimulatePhysics(true);
		StaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(SpawnedMesh);
		StaticMeshActor->SetLifeSpan(20.0f);
	}
}
