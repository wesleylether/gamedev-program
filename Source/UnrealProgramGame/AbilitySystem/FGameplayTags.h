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
	} // namespace State

} // namespace GTag