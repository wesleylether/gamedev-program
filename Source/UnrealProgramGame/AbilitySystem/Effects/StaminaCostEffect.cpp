// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaCostEffect.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"

UStaminaCostEffect::UStaminaCostEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = UPlayerAttributeSet::GetStaminaAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;

	FSetByCallerFloat SetByCallerParam;
	SetByCallerParam.DataTag = GTag::Effect::StaminaCost;

	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetByCallerParam);

	Modifiers.Add(ModifierInfo);
}