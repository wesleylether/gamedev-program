// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"

#include "BaseStaminaCostAbility.generated.h"

/**
 * Base class for abilities that have a stamina cost.
 */
UCLASS()
class UNREALPROGRAMGAME_API UBaseStaminaCostAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseStaminaCostAbility();

protected:
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Cost")
	float StaminaCostAmount;
};
