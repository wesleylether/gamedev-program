// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "StaminaGainEffect.generated.h"

/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UStaminaGainEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UStaminaGainEffect(const FObjectInitializer& ObjectInitializer);
};
