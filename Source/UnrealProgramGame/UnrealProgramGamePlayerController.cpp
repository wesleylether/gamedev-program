// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProgramGamePlayerController.h"
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
