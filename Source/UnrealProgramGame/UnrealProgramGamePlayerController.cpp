// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProgramGamePlayerController.h"
#include "6-Delegates/3-EventDrivenGameplay/Quest/EventSubsystems/QuestEventSubsystem.h"
#include "6-Delegates/3-EventDrivenGameplay/Quest/QuestHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UI/MyMainDashboard.h"
#include "UnrealProgramGame.h"
#include "UnrealProgramGameCameraManager.h"
#include "Widgets/Input/SVirtualJoystick.h"

AUnrealProgramGamePlayerController::AUnrealProgramGamePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AUnrealProgramGameCameraManager::StaticClass();
}

void AUnrealProgramGamePlayerController::UpdateStamina(float Percentage)
{
	if (MainDashboardWidget)
	{
		MainDashboardWidget->UpdateStamina(Percentage);
	}
}

void AUnrealProgramGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		}
		else
		{

			UE_LOG(LogUnrealProgramGame, Error, TEXT("Could not spawn mobile controls widget."));
		}
	}

	if (MainDashboardClass)
	{
		MainDashboardWidget = CreateWidget<UMyMainDashboard>(this, MainDashboardClass);
		if (MainDashboardWidget)
		{
			MainDashboardWidget->AddToViewport();
		}
	}

	if (QuestHUDClass)
	{
		QuestHUDWidget = CreateWidget<UQuestHUD>(this, QuestHUDClass);
		if (QuestHUDWidget)
		{
			QuestHUDWidget->ShowQuest(false);
			QuestHUDWidget->AddToViewport();
		}
	}

	QuestEventSubsystem = GetWorld()->GetSubsystem<UQuestEventSubsystem>();
	checkf(QuestEventSubsystem, TEXT("QuestGiver: QuestEventSubsystem is not found!"));

	QuestEventSubsystem->OnQuestStateChanged.AddUniqueDynamic(this, &AUnrealProgramGamePlayerController::OnQuestEvent);
	QuestEventSubsystem->OnQuestItemCollected.AddUniqueDynamic(this, &AUnrealProgramGamePlayerController::OnQuestItemCollected);
}

void AUnrealProgramGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool AUnrealProgramGamePlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void AUnrealProgramGamePlayerController::OnQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator)
{
	switch (State)
	{
		case EQuestTriggerState::Started:
			// Todo create a more reliable way to handle quest data
			if (Tag == GTag::Quests::Quest_1)
			{
				QuestHUDWidget->SetQuestTitle(FString("Quest 1"));
				QuestHUDWidget->SetQuestInfo(FString("Eat all the hamburgers"));
				QuestHUDWidget->SetQuestStatus(0, ItemsTotal);
				QuestHUDWidget->ShowQuest(true);
			}
			if (Tag == GTag::Quests::Quest_2)
			{
				QuestHUDWidget->SetQuestTitle(FString("Quest 2"));
				QuestHUDWidget->SetQuestInfo(FString("Eat all the other stuff"));
				QuestHUDWidget->SetQuestStatus(0, ItemsTotal);
				QuestHUDWidget->ShowQuest(true);
			}

			break;

		case EQuestTriggerState::Completed:
			QuestHUDWidget->ShowQuest(false);
			break;

		default:
			break;
	}
}

void AUnrealProgramGamePlayerController::OnQuestItemCollected(FGameplayTag Tag, int32 ItemsCollected, int32 ItemsTotal)
{
	QuestHUDWidget->SetQuestStatus(ItemsCollected, ItemsTotal);
}
