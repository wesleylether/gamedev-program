#include "TrafficLight.h"

ATrafficLight::ATrafficLight()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	ChangeColorToGreen();
}

void ATrafficLight::ChangeColorToGreen()
{
	if (!IsValid(DynamicMaterial))
		return;

	UE_LOG(LogTemp, Warning, TEXT("ChangeColorToGreen"));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(0.0f, 1.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToYellow, GreenTimerLength);
}

void ATrafficLight::ChangeColorToYellow()
{
	if (!IsValid(DynamicMaterial))
		return;

	UE_LOG(LogTemp, Warning, TEXT("ChangeColorToYellow"));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(1.0f, 1.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToRed, YellowTimerLength);
}

void ATrafficLight::ChangeColorToRed()
{
	if (!IsValid(DynamicMaterial))
		return;

	UE_LOG(LogTemp, Warning, TEXT("ChangeColorToRed"));

	DynamicMaterial->SetVectorParameterValue("Color", FLinearColor(1.0f, 0.0f, 0.0f));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::ChangeColorToGreen, RedTimerLength);
}
