#include "FGameplayTags.h"

#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"

namespace GTag
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(None, "GTags.None", "None")

	namespace Abilities
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dash, "GTags.Abilities.Player.Dash", "Tag for dash ability")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Run, "GTags.Abilities.Player.Run", "Tag for run ability")

		} // namespace Player

		namespace State
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dashing, "GTags.Abilities.State.Dashing", "Tag for dashing state")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Running, "GTags.Abilities.State.Running", "Tag for running state")

		} // namespace State
	} // namespace Abilities

	namespace Effect
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(StaminaCost, "GTags.Abilities.Effect.StaminaCost", "Tag for stamina cost effect")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(StaminaDrain, "GTags.Abilities.Effect.StaminaDrain", "Tag for stamina drain effect")

	} // namespace Effect
} // namespace GTag