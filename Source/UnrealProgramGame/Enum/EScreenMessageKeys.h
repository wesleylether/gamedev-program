#pragma once

#include "CoreMinimal.h"
#include "EScreenMessageKeys.generated.h"

/**
 * Enum for GEngine on-screen message keys to avoid hardcoding numbers.
 * When using GEngine->AddOnScreenDebugMessage, cast these to int32 or uint64.
 * Example: GEngine->AddOnScreenDebugMessage((uint64)EScreenMessageKey::Input_Rotation, ...)
 */
UENUM(BlueprintType)
enum class EScreenMessageKey : uint8
{
	None UMETA(DisplayName = "None / Default"),

	// Input Debugging
	Input_Rotation UMETA(DisplayName = "Input: Rotation"),
	Input_Ongoing UMETA(DisplayName = "Input: Ongoing"),
	Input_Triggered UMETA(DisplayName = "Input: Triggered"),

	// Overlap / Detection
	Overlap_General UMETA(DisplayName = "Overlap: General"),
	Overlap_ActorList UMETA(DisplayName = "Overlap: Actor List"),

	// Specific Objects
	PressurePlate_Status UMETA(DisplayName = "Pressure Plate: Status"),
	PressurePlate_Tags UMETA(DisplayName = "Pressure Plate: Tags"),

	// Gameplay Systems
	Counter UMETA(DisplayName = "System: Counter"),
	Geyser_Status UMETA(DisplayName = "System: Geyser Status"),
	StockKeeper_Status UMETA(DisplayName = "System: Stock Keeper Status"),

	// Timer Trouble
	TimerTrouble_ElapsedTime UMETA(DisplayName = "System: Timer Trouble Elapsed Time"),
	TimerTrouble_Paused UMETA(DisplayName = "System: Timer Trouble Paused"),
	Spawning_Bom UMETA(DisplayName = "System: Spawning Bomb"),

	// Trace Trails
	Trace_FirstTrace UMETA(DisplayName = "System: Trace First Trace"),
	Trace_Distance UMETA(DisplayName = "System: Trace Distance"),
	Trace_StopHittingYourself UMETA(DisplayName = "System: Trace Stop Hitting Yourself"),
	Trace_XRayTrace UMETA(DisplayName = "System: Trace X-Ray Trace"),
	Trace_Sentry UMETA(DisplayName = "System: Trace Sentry"),

	// Sweep Squad
	SweepHit UMETA(DisplayName = "System: Sweep Hit"),
	LineHit UMETA(DisplayName = "System: Line Hit"),
	Sweep_Multi UMETA(DisplayName = "System: Sweep Multi"),
	Sweep_AreaScanner UMETA(DisplayName = "System: Sweep Area Scanner"),
};
