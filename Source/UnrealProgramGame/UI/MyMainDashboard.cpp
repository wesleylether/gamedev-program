// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MyMainDashboard.h"

#include "Components/ProgressBar.h"

void UMyMainDashboard::UpdateStamina(float Percentage)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(FMath::Clamp(Percentage, 0.0f, 1.0f));
	}
}