// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "StaminaCostEffect.generated.h"

/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UStaminaCostEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UStaminaCostEffect();
};

UCLASS()
class UNREALPROGRAMGAME_API UStaminaDrainEffect : public UStaminaCostEffect
{
	GENERATED_BODY()

public:
	UStaminaDrainEffect();
};

UCLASS()
class UNREALPROGRAMGAME_API UStaminaInstantEffect : public UStaminaCostEffect
{
	GENERATED_BODY()

public:
	UStaminaInstantEffect();
};
