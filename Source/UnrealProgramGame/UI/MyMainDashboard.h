// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MyMainDashboard.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UMyMainDashboard : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateStamina(float Percentage);

	void HighlightPrompt(FString Text, float Duration = 1.0f, FLinearColor Color = FLinearColor::White);
	void ShowPrompt(bool Enable);
	void ShowCrossHair(bool Enable);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CrossHairBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CrossHairActive;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Prompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DefaultPromptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PromptDuration = 3.0f;

	virtual void NativeConstruct() override;

private:
	FTimerHandle PromptHandle;
	bool bPromptActive = false;
	bool bCrossHairActive = false;

	UFUNCTION()
	void OnPromptTimer();
};
