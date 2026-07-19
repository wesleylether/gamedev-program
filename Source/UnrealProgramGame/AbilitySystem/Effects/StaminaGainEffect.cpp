// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaGainEffect.h"

#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"

UStaminaGainEffect::UStaminaGainEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 0.1f;
	PeriodicInhibitionPolicy = EGameplayEffectPeriodInhibitionRemovedPolicy::NeverReset;

	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = UPlayerAttributeSet::GetStaminaAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;

	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(0.5f));
	Modifiers.Add(ModifierInfo);

	UTargetTagRequirementsGameplayEffectComponent* TagRequirementsComponent = ObjectInitializer.CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(this, TEXT("TargetTagRequirementsComponent"));
	GEComponents.AddUnique(TagRequirementsComponent);

	FGameplayTagRequirements& OngoingRequirements = TagRequirementsComponent->OngoingTagRequirements;
	OngoingRequirements.IgnoreTags.AddTag(GTag::State::Running);
	OngoingRequirements.IgnoreTags.AddTag(GTag::State::Flying);
}