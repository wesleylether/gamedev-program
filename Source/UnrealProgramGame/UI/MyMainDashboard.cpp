// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MyMainDashboard.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyMainDashboard::NativeConstruct()
{
	Super::NativeConstruct();

	DefaultPromptText = FString("Press [E] to interact");
	CrossHairActive->SetVisibility(ESlateVisibility::Hidden);
	Prompt->SetVisibility(ESlateVisibility::Hidden);
}

void UMyMainDashboard::UpdateStamina(float Percentage)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(FMath::Clamp(Percentage, 0.0f, 1.0f));
	}
}

void UMyMainDashboard::HighlightPrompt(FString Text, float Duration, FLinearColor Color)
{
	if (Duration <= 0.0f)
		return;

	if (Duration > PromptDuration)
		Duration = PromptDuration;

	if (bPromptActive)
		return;

	bPromptActive = true;
	Prompt->SetColorAndOpacity(FSlateColor(Color));
	Prompt->SetText(FText::FromString(Text));
	ShowPrompt(true);
	GetWorld()->GetTimerManager().SetTimer(PromptHandle, this, &UMyMainDashboard::OnPromptTimer, Duration, false);
}

void UMyMainDashboard::ShowPrompt(bool Enable)
{
	if (!Enable && bPromptActive)
		return;

	const ESlateVisibility Visibility = Enable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	if (Prompt->GetVisibility() != Visibility)
		Prompt->SetVisibility(Visibility);
}

void UMyMainDashboard::ShowCrossHair(bool Enable)
{
	const ESlateVisibility Visibility = Enable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	if (CrossHairActive->GetVisibility() != Visibility)
		CrossHairActive->SetVisibility(Visibility);
}

void UMyMainDashboard::OnPromptTimer()
{
	bPromptActive = false;

	ShowPrompt(false);
	Prompt->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Prompt->SetText(FText::FromString(DefaultPromptText));
}
