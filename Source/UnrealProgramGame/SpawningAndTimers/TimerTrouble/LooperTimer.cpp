#include "LooperTimer.h"

ALooperTimer::ALooperTimer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALooperTimer::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALooperTimer::ChangeColor, TimerLength, true);
}

void ALooperTimer::ChangeColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}
