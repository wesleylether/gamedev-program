#include "TimerLimit.h"

ATimerLimit::ATimerLimit()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATimerLimit::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

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
