#include "LooperTimer.h"

void ALooperTimer::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

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
