// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestHUD.h"

#include "Components/TextBlock.h"

void UQuestHUD::SetTextBlockText(UTextBlock* TextBlock, FString Text)
{
	TextBlock->SetText(FText::FromString(Text));
}

void UQuestHUD::ShowQuest(bool bShouldShow)
{
	ESlateVisibility Visibility = bShouldShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	SetVisibility(Visibility);
}

void UQuestHUD::SetQuestTitle(FString Title)
{
	SetTextBlockText(QuestTitle, Title);
}

void UQuestHUD::SetQuestInfo(FString Info)
{
	SetTextBlockText(QuestInfo, Info);
}

void UQuestHUD::SetQuestStatus(int32 CollectedItemCount, int32 TotalItemCount)
{
	FString StatusText = FString::Printf(TEXT("Collected %d/%d"), CollectedItemCount, TotalItemCount);
	SetTextBlockText(QuestStatus, StatusText);
}