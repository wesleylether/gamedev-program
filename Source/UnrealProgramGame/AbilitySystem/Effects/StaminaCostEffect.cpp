// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaCostEffect.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"

UStaminaCostEffect::UStaminaCostEffect()
{
	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = UPlayerAttributeSet::GetStaminaAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;

	FSetByCallerFloat StaminaCost;
	StaminaCost.DataTag = GTag::Effect::StaminaCost;

	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(StaminaCost);

	Modifiers.Add(ModifierInfo);
}

UStaminaDrainEffect::UStaminaDrainEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 0.1f;
}

UStaminaInstantEffect::UStaminaInstantEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}