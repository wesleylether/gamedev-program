// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/Base/BaseStaminaCostAbility.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UBaseStaminaCostAbility::UBaseStaminaCostAbility()
{
	StaminaCostAmount = 0.0f;
}

bool UBaseStaminaCostAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!CostGameplayEffectClass)
	{
		return true;
	}

	if (UAbilitySystemComponent* ASC = ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr)
	{
		float CurrentStamina = ASC->GetNumericAttribute(UPlayerAttributeSet::GetStaminaAttribute());
		if (CurrentStamina < StaminaCostAmount)
		{
			const FGameplayTag& CostTag = UAbilitySystemGlobals::Get().ActivateFailCostTag;
			if (OptionalRelevantTags && CostTag.IsValid())
			{
				OptionalRelevantTags->AddTag(CostTag);
			}
			return false;
		}
	}
	return true;
}

void UBaseStaminaCostAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if (CostGameplayEffectClass && HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, CostGameplayEffectClass, GetAbilityLevel(Handle, ActorInfo));
		if (SpecHandle.IsValid() && SpecHandle.Data.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(GTag::Effect::StaminaCost, -StaminaCostAmount);
			(void)ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}
}
