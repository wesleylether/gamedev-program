#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FGameplayTags
{
	static const FGameplayTags& Get() { return GameplayTags; }

	static void Initialize();

	// Abilities
	FGameplayTag Ability_Run;
	FGameplayTag Ability_Dash;

	// States
	FGameplayTag State_Running;
	FGameplayTag State_Dashing;

	// Effects
	FGameplayTag Effect_StaminaCost;
	FGameplayTag Effect_StaminaDrain;

private:
	static FGameplayTags GameplayTags;
};