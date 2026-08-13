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
	None = 0 UMETA(DisplayName = "None / Default"),

	// Input Debugging
	Input_Rotation = 1 UMETA(DisplayName = "Input: Rotation"),
	Input_Ongoing = 2 UMETA(DisplayName = "Input: Ongoing"),
	Input_Triggered = 3 UMETA(DisplayName = "Input: Triggered"),

	// Overlap / Detection
	Overlap_General = 4 UMETA(DisplayName = "Overlap: General"),
	Overlap_ActorList = 5 UMETA(DisplayName = "Overlap: Actor List"),

	// Specific Objects
	PressurePlate_Status = 7 UMETA(DisplayName = "Pressure Plate: Status"),
	PressurePlate_Tags = 8 UMETA(DisplayName = "Pressure Plate: Tags"),

	// Gameplay Systems
	Counter = 10 UMETA(DisplayName = "System: Counter"),
	Geyser_Status = 11 UMETA(DisplayName = "System: Geyser Status"),
	StockKeeper_Status = 12 UMETA(DisplayName = "System: Stock Keeper Status"),

	// Timer Trouble
	TimerTrouble_ElapsedTime = 13 UMETA(DisplayName = "System: Timer Trouble Elapsed Time"),
	TimerTrouble_Paused = 14 UMETA(DisplayName = "System: Timer Trouble Paused"),

	// Trace Trails
	Trace_FirstTrace = 15 UMETA(DisplayName = "System: Trace First Trace"),

	// Spawning and Timers
	Spawning_Bom = 16 UMETA(DisplayName = "System: Spawning Bomb")
};
