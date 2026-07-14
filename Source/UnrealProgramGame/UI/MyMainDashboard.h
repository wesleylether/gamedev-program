// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MyMainDashboard.generated.h"

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

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;
};
