#include "TrafficLight.h"

void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

	ChangeColorToGreen();
}

void ATrafficLight::ChangeColorToGreen()
{
	if (!IsValid(DynamicMaterial))
		return;

	Log(FString::Printf(TEXT("ChangeColorToGreen")));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(0.0f, 1.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToYellow, GreenTimerLength);
}

void ATrafficLight::ChangeColorToYellow()
{
	if (!IsValid(DynamicMaterial))
		return;

	Log(FString::Printf(TEXT("ChangeColorToYellow")));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(1.0f, 1.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToRed, YellowTimerLength);
}

void ATrafficLight::ChangeColorToRed()
{
	if (!IsValid(DynamicMaterial))
		return;

	Log(FString::Printf(TEXT("ChangeColorToRed")));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(1.0f, 0.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToGreen, RedTimerLength);
}
