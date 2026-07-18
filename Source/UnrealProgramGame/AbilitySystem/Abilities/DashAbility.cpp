// Fill out your copyright notice in the Description page of Project Settings.

#include "DashAbility.h"

#include "AbilitySystem/Effects/StaminaCostEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "UnrealProgramGameCharacter.h"

UDashAbility::UDashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	DashForce = 3000.0f;
	StaminaCostAmount = 15.0f;

	SetAssetTags(FGameplayTagContainer(GTag::Abilities::Dash));
	ActivationOwnedTags.AddTag(GTag::State::Dashing);
	CancelAbilitiesWithTag.AddTag(GTag::Abilities::Run);
	ActivationBlockedTags.AddTag(GTag::State::Dashing);

	CostGameplayEffectClass = UStaminaInstantEffect::StaticClass();
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get()))
	{
		FVector2D MoveInput = Character->GetLastDashInput2D();
		FVector	  DashDirection;

		if (MoveInput.IsNearlyZero())
		{
			DashDirection = Character->GetActorForwardVector();
		}
		else
		{
			// Calculate dash direction based on movement input (X = Right, Y = Forward)
			DashDirection = Character->GetActorForwardVector() * MoveInput.Y + Character->GetActorRightVector() * MoveInput.X;
			DashDirection.Normalize();
		}

		Character->LaunchCharacter(DashDirection * DashForce, true, true);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
