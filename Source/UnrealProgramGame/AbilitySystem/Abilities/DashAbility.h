// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"
#include "DashAbility.generated.h"

/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UDashAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDashAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float DashForce;
};
