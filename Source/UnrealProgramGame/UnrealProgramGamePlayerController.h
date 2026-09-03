// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "6-Delegates/3-EventDrivenGameplay/Quest/QuestHUD.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnrealProgramGamePlayerController.generated.h"

enum class EQuestTriggerState : uint8;
struct FGameplayTag;
class UQuestEventSubsystem;
class UQuestHUD;
class UMyMainDashboard;
class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config = "Game")
class UNREALPROGRAMGAME_API AUnrealProgramGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Constructor */
	AUnrealProgramGamePlayerController();

	void UpdateStamina(float Percentage);

	TObjectPtr<UMyMainDashboard> GetMainDashboard() const { return MainDashboardWidget; }

	TObjectPtr<UQuestHUD> GetQuestHUD() const { return QuestHUDWidget; }

protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<TObjectPtr<UInputMappingContext>> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMyMainDashboard> MainDashboardClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UQuestHUD> QuestHUDClass;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	UFUNCTION()
	void OnQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator);

	UFUNCTION()
	void OnQuestItemCollected(FGameplayTag Tag, int32 ItemsCollected, int32 ItemsTotal);

private:
	UPROPERTY()
	TObjectPtr<UMyMainDashboard> MainDashboardWidget;

	UPROPERTY()
	TObjectPtr<UQuestHUD> QuestHUDWidget;

	UPROPERTY()
	TObjectPtr<UQuestEventSubsystem> QuestEventSubsystem;
};
