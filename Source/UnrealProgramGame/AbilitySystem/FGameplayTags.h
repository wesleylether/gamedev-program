#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GTag
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(None);

	namespace Abilities
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dash);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Run);
		} // namespace Player

		namespace State
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dashing);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running);
		} // namespace State

	} // namespace Abilities

	namespace Effect
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(StaminaCost);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(StaminaDrain);
	} // namespace Effect

} // namespace GTags