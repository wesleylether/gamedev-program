// Fill out your copyright notice in the Description page of Project Settings.

#include "ChargedJumpAbility.h"

#include "AbilitySystem/Effects/StaminaCostEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealProgramGameCharacter.h"

UChargedJumpAbility::UChargedJumpAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	JumpForce = 1200.0f;
	StaminaCostAmount = 25.0f;

	SetAssetTags(FGameplayTagContainer(GTag::Abilities::ChargedJump));
	ActivationOwnedTags.AddTag(GTag::State::Jumping);

	ActivationBlockedTags.AddTag(GTag::State::Flying);
	ActivationBlockedTags.AddTag(GTag::State::Dashing);
	ActivationBlockedTags.AddTag(GTag::State::Crouching);
	ActivationBlockedTags.AddTag(GTag::State::Exhausted);
	ActivationBlockedTags.AddTag(GTag::State::InMud);

	CostGameplayEffectClass = UStaminaInstantEffect::StaticClass();
}

void UChargedJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	CachedCharacter = Cast<AUnrealProgramGameCharacter>(ActorInfo->AvatarActor.Get());
	if (!CachedCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (UCharacterMovementComponent* MovementComponent = CachedCharacter->GetCharacterMovement())
	{
		MovementComponent->JumpZVelocity = JumpForce;
		CachedCharacter->Jump();

		CachedCharacter->LandedDelegate.AddDynamic(this, &UChargedJumpAbility::HandleCharacterLanded);

		if (CachedCharacter->GetChargedJumpSound())
		{
			UGameplayStatics::PlaySoundAtLocation(this, CachedCharacter->GetChargedJumpSound(), CachedCharacter->GetActorLocation());
		}
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UChargedJumpAbility::HandleCharacterLanded(const FHitResult& Hit)
{
	K2_EndAbility();
}

void UChargedJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (CachedCharacter)
	{
		CachedCharacter->LandedDelegate.RemoveDynamic(this, &UChargedJumpAbility::HandleCharacterLanded);

		if (UCharacterMovementComponent* MovementComponent = CachedCharacter->GetCharacterMovement())
		{
			MovementComponent->JumpZVelocity = CachedCharacter->GetMaxJumpVelocity();
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
