#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "QuestHUD.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class UNREALPROGRAMGAME_API UQuestHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> QuestBackgroundImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestStatus;

	void SetTextBlockText(UTextBlock* TextBlock, FString Text);

	void ShowQuest(bool bShouldShow);

	void SetQuestTitle(FString Title);

	void SetQuestInfo(FString Info);

	void SetQuestStatus(int32 CollectedItemCount, int32 TotalItemCount);
};
