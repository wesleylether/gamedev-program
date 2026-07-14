#include "AbilitySystem/UnrealProgramAttributeSet.h"
#include "GameplayEffectExtension.h"

UUnrealProgramAttributeSet::UUnrealProgramAttributeSet()
{
}

void UUnrealProgramAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}
