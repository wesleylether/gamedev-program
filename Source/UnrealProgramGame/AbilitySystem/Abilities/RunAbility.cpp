// Fill out your copyright notice in the Description page of Project Settings.

#include "RunAbility.h"

#include "AbilitySystem/Effects/StaminaCostEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealProgramGameCharacter.h"

URunAbility::URunAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	SprintSpeedMultiplier = 1.8f;
	StaminaCostAmount = 1.0f;

	SetAssetTags(FGameplayTagContainer(GTag::Abilities::Run));
	ActivationOwnedTags.AddTag(GTag::State::Running);

	CostGameplayEffectClass = UStaminaDrainEffect::StaticClass();
}

void URunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get()); Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxWalkSpeed() * SprintSpeedMultiplier;
	}
}

void URunAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get()); Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxWalkSpeed();
	}

	if (ActiveCostEffectHandle.IsValid() && ActorInfo->AbilitySystemComponent.IsValid())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveCostEffectHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}