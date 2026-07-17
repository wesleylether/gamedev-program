// Fill out your copyright notice in the Description page of Project Settings.

#include "DashAbility.h"

#include "AbilitySystem/Effects/StaminaCostEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "GameFramework/Character.h"

UDashAbility::UDashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	DashForce = 2000.0f;

	SetAssetTags(FGameplayTagContainer(GTag::Abilities::Player::Dash));
	ActivationOwnedTags.AddTag(GTag::Abilities::State::Dashing);
	CancelAbilitiesWithTag.AddTag(GTag::Abilities::Player::Run);
	ActivationBlockedTags.AddTag(GTag::Abilities::State::Dashing);

	CostGameplayEffectClass = UStaminaCostEffect::StaticClass();
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CostGameplayEffectClass, 1.0f);

		if (SpecHandle.IsValid())
		{
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(GTag::Effect::StaminaCost, -20.0f);

			(void)ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}

	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()))
	{
		FVector DashDirection = Character->GetActorForwardVector();
		Character->LaunchCharacter(DashDirection * DashForce, true, true);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
