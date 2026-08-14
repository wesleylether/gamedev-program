#include "TimerLimit.h"

void ATimerLimit::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerLimit::ChangeColor, TimerLength, true);
}

void ATimerLimit::ChangeColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);

	if (++TimerCount >= TimerLimit)
		GetWorldTimerManager().ClearTimer(TimerHandle);
}
