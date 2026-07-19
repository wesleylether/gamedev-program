// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/BaseStaminaCostAbility.h"
#include "CoreMinimal.h"

#include "ChargedJumpAbility.generated.h"

class AUnrealProgramGameCharacter;
/**
 *
 */
UCLASS()
class UNREALPROGRAMGAME_API UChargedJumpAbility : public UBaseStaminaCostAbility
{
	GENERATED_BODY()

public:
	UChargedJumpAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void HandleCharacterLanded(const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float JumpForce;

	UPROPERTY()
	TObjectPtr<AUnrealProgramGameCharacter> CachedCharacter;
};
