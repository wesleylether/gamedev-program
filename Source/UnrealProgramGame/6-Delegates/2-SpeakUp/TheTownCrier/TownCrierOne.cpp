#include "TownCrierOne.h"

#include "6-Delegates/2-SpeakUp/TheTownCrier.h"

void ATownCrierOne::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (!TownCrier)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

	TownCrier->OnSpeakUp.AddUniqueDynamic(this, &ATownCrierOne::ChangeColor);
}

void ATownCrierOne::ChangeColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}
