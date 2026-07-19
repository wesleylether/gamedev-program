// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/BaseStaminaCostAbility.h"
#include "CoreMinimal.h"
#include "FlyAbility.generated.h"

/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UFlyAbility : public UBaseStaminaCostAbility
{
	GENERATED_BODY()

public:
	UFlyAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
