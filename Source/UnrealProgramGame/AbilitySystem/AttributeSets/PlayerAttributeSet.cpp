#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/FGameplayTags.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitMaxStamina(100.f);
	InitStamina(100.f);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute CurrentAttribute = Data.EvaluatedData.Attribute;
	if (CurrentAttribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}

void UPlayerAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetStaminaAttribute())
	{
		if (NewValue <= 0.0f)
		{
			if (UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
			{
				ASC->AddLooseGameplayTag(GTag::State::Exhausted);

				FGameplayTagContainer AbilitiesToCancel;
				AbilitiesToCancel.AddTag(GTag::Abilities::Run);
				AbilitiesToCancel.AddTag(GTag::Abilities::Fly);
				ASC->CancelAbilities(&AbilitiesToCancel);
			}
		}

		if (NewValue >= GetMaxStamina())
		{
			if (UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
			{
				if (ASC->HasMatchingGameplayTag(GTag::State::Exhausted))
				{
					ASC->RemoveLooseGameplayTag(GTag::State::Exhausted);
				}
			}
		}
	}
}
