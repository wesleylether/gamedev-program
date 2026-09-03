#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GTag
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(None);

	namespace Abilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dash);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Run);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fly);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ChargedJump);
	} // namespace Abilities

	namespace Effect
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(StaminaCost);
	} // namespace Effect

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dashing);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Flying);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Jumping);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exhausted);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InMud);
	} // namespace State

	namespace Interactable
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Any);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pickup);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Push);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interact);
	} // namespace Interactable

	namespace Quests
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_1);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_2);
	} // namespace Quests

} // namespace GTag