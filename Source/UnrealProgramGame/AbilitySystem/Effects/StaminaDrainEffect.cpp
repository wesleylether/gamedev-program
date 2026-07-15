// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaDrainEffect.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"

UStaminaDrainEffect::UStaminaDrainEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 0.1f;

	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = UPlayerAttributeSet::GetStaminaAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-1.0f));

	Modifiers.Add(ModifierInfo);
}