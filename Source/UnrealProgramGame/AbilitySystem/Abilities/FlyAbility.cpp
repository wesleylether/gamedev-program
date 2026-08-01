// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyAbility.h"

#include "AbilitySystem/Effects/StaminaCostEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealProgramGameCharacter.h"

class AUnrealProgramGameCharacter;

UFlyAbility::UFlyAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	StaminaCostAmount = 1.0f;

	SetAssetTags(FGameplayTagContainer(GTag::Abilities::Fly));
	ActivationOwnedTags.AddTag(GTag::State::Flying);

	ActivationBlockedTags.AddTag(GTag::State::Jumping);
	ActivationBlockedTags.AddTag(GTag::State::Dashing);
	ActivationBlockedTags.AddTag(GTag::State::Exhausted);
	ActivationBlockedTags.AddTag(GTag::State::InMud);

	CostGameplayEffectClass = UStaminaDrainEffect::StaticClass();
}

void UFlyAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get()); Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void UFlyAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get()); Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}

	if (ActiveCostEffectHandle.IsValid() && ActorInfo->AbilitySystemComponent.IsValid())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveCostEffectHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}