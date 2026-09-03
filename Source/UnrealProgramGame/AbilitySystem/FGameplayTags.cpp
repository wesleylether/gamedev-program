#include "FGameplayTags.h"

#include "NativeGameplayTags.h"

namespace GTag
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(None, "GTags.None", "None")

	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dash, "GTags.Abilities.Player.Dash", "Tag for dash ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Run, "GTags.Abilities.Player.Run", "Tag for run ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fly, "GTags.Abilities.Player.Fly", "Tag for fly ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ChargedJump, "GTags.Abilities.Player.ChargedJump", "Tag for charged jump ability")
	} // namespace Abilities

	namespace Effect
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(StaminaCost, "GTags.Abilities.Effect.StaminaCost", "Tag for stamina cost effect")
	} // namespace Effect

	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dashing, "GTags.State.Dashing", "Tag for dashing state")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Running, "GTags.State.Running", "Tag for running state")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Flying, "GTags.State.Flying", "Tag for flying state")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Jumping, "GTags.State.Jumping", "Tag for jumping state")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Exhausted, "GTags.State.Exhausted", "Tag for exhausted state")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(InMud, "GTags.State.InMud", "Tag for in mud state")
	} // namespace State

	namespace Interactable
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Any, "GTags.Interactable", "Tag for all interactable tags")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Pickup, "GTags.Interactable.Pickup", "Tag for interactable object to Pickup")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Push, "GTags.Interactable.Push", "Tag for interactable object to Push")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interact, "GTags.Interactable.Interact", "Tag for interactable object to Interact")
	} // namespace Interactable

	namespace Quests
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Quest_1, "GTags.Quests.Quest_1", "Tag for quest 1")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Quest_2, "GTags.Quests.Quest_2", "Tag for quest 2")
	} // namespace Quests
} // namespace GTag