#include "FGameplayTags.h"

#include "GameplayTagsManager.h"

FGameplayTags FGameplayTags::GameplayTags;

void FGameplayTags::Initialize()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	// Abilities
	GameplayTags.Ability_Run = Manager.AddNativeGameplayTag(TEXT("Ability.Run"));
	GameplayTags.Ability_Dash = Manager.AddNativeGameplayTag(TEXT("Ability.Dash"));

	// States
	GameplayTags.State_Running = Manager.AddNativeGameplayTag(TEXT("State.Running"));
	GameplayTags.State_Dashing = Manager.AddNativeGameplayTag(TEXT("State.Dashing"));

	// Effects
	GameplayTags.Effect_StaminaCost = Manager.AddNativeGameplayTag(TEXT("Effect.StaminaCost"));
	GameplayTags.Effect_StaminaDrain = Manager.AddNativeGameplayTag(TEXT("Effect.StaminaDrain"));
}