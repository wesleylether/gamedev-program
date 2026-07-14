// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProgramGameCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/UnrealProgramAttributeSet.h"
#include "UnrealProgramGamePlayerController.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UnrealProgramGame.h"

AUnrealProgramGameCharacter::AUnrealProgramGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f),
		FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanFly = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UUnrealProgramAttributeSet>(TEXT("AttributeSet"));

	PrimaryActorTick.bCanEverTick = true;
}

void AUnrealProgramGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::DoJumpEnd);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DoChargedJumpStart);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::DoChargedJumpEnd);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::FlyUp);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::MoveInput);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::CrouchInput);
		EnhancedInputComponent->BindAction(DashedAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::DashedStarted);
		EnhancedInputComponent->BindAction(DashedAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DashedTriggered);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::LookInput);

		// Trigger State Tests Module 1-1
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::TriggerStateTestStarted);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerStateTestCompleted);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Canceled, this, &AUnrealProgramGameCharacter::TriggerStateTestCanceled);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerStateTestTriggered);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::TriggerStateTestOngoing);

		// Rotate Module 1-2
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RotateInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::RotateTriggerOngoing);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RotateTriggerTriggered);
		EnhancedInputComponent->BindAction(TriggerAimAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerAimInputTriggered);
		EnhancedInputComponent->BindAction(TriggerAimAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerAimInputCompleted);
		EnhancedInputComponent->BindAction(TriggerInvertAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerInvertInput);

		// Trigger Qualifiers Module 1-3
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::TriggerQualifierStarted);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerQualifierCompleted);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Canceled, this, &AUnrealProgramGameCharacter::TriggerQualifierCanceled);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerQualifierTriggered);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::TriggerQualifierOngoing);

		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::WalkInputTriggered);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RunInputTriggered);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::FlyDown);

		EnhancedInputComponent->BindAction(FlyModeAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::FlyInput);
	}
	else
	{
		UE_LOG(LogUnrealProgramGame, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUnrealProgramGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	if (AttributeSet)
	{
		AttributeSet->SetMaxStamina(100.0f);
		AttributeSet->SetStamina(100.0f);
	}

	DefaultCameraRelativeLocation = FirstPersonCameraComponent->GetRelativeLocation();
	TargetCameraRelativeLocation = DefaultCameraRelativeLocation;
}

void AUnrealProgramGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttributeSet)
	{
		float CurrentStamina = AttributeSet->GetStamina();
		float MaxStamina = AttributeSet->GetMaxStamina();

		// Handle Regeneration
		if (CurrentStamina < MaxStamina)
		{
			AttributeSet->SetStamina(FMath::Min(CurrentStamina + StaminaRegenRate * DeltaTime, MaxStamina));
		}

		// Handle Run Consumption
		if (GetCharacterMovement()->MaxWalkSpeed == MaxRunSpeed && GetVelocity().Size() > 0.0f)
		{
			if (CurrentStamina > 0.0f)
			{
				AttributeSet->SetStamina(FMath::Max(AttributeSet->GetStamina() - RunStaminaCost * DeltaTime, 0.0f));
			}
			else
			{
				// Out of stamina, stop running
				GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
			}
		}

		// Depleted Message
		if (AttributeSet->GetStamina() <= 0.0f)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(100, 0.1f, FColor::Red, TEXT("Stamina depleted"));
			}
		}

		// Update UI
		if (AUnrealProgramGamePlayerController* PC = Cast<AUnrealProgramGamePlayerController>(GetController()))
		{
			PC->UpdateStamina(MaxStamina > 0.0f ? AttributeSet->GetStamina() / MaxStamina : 0.0f);
		}
	}

	FVector CurrentLocation = FirstPersonCameraComponent->GetRelativeLocation();
	if (!CurrentLocation.Equals(TargetCameraRelativeLocation))
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetCameraRelativeLocation, DeltaTime, CameraInterpSpeed);
		FirstPersonCameraComponent->SetRelativeLocation(NewLocation);
	}
}

void AUnrealProgramGameCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	TargetCameraRelativeLocation = DefaultCameraRelativeLocation + FVector(-CrouchedCameraOffset, 0.0f, 0.0f);
}

void AUnrealProgramGameCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	TargetCameraRelativeLocation = DefaultCameraRelativeLocation;
}

void AUnrealProgramGameCharacter::TriggerAimInputTriggered(const FInputActionValue& Value)
{
	bIsAiming = true;
}

void AUnrealProgramGameCharacter::TriggerAimInputCompleted(const FInputActionValue& Value)
{
	bIsAiming = false;
}

void AUnrealProgramGameCharacter::TriggerInvertInput(const FInputActionValue& Value)
{
	bIsInverting = !bIsInverting;
}

void AUnrealProgramGameCharacter::FlyInput()
{
	if (PlayerState == EPlayerState::Flying)
	{
		PlayerState = EPlayerState::Walking;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		PlayerState = EPlayerState::Flying;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void AUnrealProgramGameCharacter::FlyUp()
{
	AddMovementInput(FVector::UpVector, 1.0f);
}

void AUnrealProgramGameCharacter::FlyDown()
{
	AddMovementInput(FVector::UpVector, -1.0f);
}

void AUnrealProgramGameCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AUnrealProgramGameCharacter::WalkInputTriggered(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxSneakSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void AUnrealProgramGameCharacter::RunInputTriggered(const FInputActionValue& Value)
{
	if (PlayerState == EPlayerState::Flying)
	{
		return;
	}

	if (Value.Get<bool>() && AttributeSet && AttributeSet->GetStamina() > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void AUnrealProgramGameCharacter::DashedStarted(const FInputActionValue& Values)
{
	FVector2D CurrentInput = Values.Get<FVector2D>();

	if (!CurrentInput.IsNearlyZero())
	{
		PreviousDashInput2D = LastDashInput2D;
		LastDashInput2D = CurrentInput;
	}
}

void AUnrealProgramGameCharacter::DashedTriggered(const FInputActionValue& Values)
{
	if (GetWorldTimerManager().IsTimerActive(DashTimerHandle))
	{
		return;
	}

	if (!AttributeSet || AttributeSet->GetStamina() < DashStaminaCost)
	{
		return;
	}

	if (!LastDashInput2D.Equals(PreviousDashInput2D, 0.1f))
	{
		LastDashInput2D = FVector2D::ZeroVector;
		PreviousDashInput2D = FVector2D::ZeroVector;
		return;
	}

	if (!LastDashInput2D.IsNearlyZero())
	{
		FVector DashDirection = GetActorForwardVector() * LastDashInput2D.Y + GetActorRightVector() * LastDashInput2D.X;
		DashDirection.Normalize();

		LaunchCharacter(DashDirection * DashSpeed, true, true);

		AttributeSet->SetStamina(AttributeSet->GetStamina() - DashStaminaCost);

		if (DashSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DashSound, GetActorLocation());
		}

		GetWorldTimerManager().SetTimer(DashTimerHandle, this, &AUnrealProgramGameCharacter::StopDash, DashTiming, false);

		LastDashInput2D = FVector2D::ZeroVector;
		PreviousDashInput2D = FVector2D::ZeroVector;
	}
}

void AUnrealProgramGameCharacter::StopDash()
{
	GetCharacterMovement()->StopMovementImmediately();
}

void AUnrealProgramGameCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	if (bIsInverting)
	{
		DoAim(LookAxisVector.X * -1.0f, LookAxisVector.Y * -1.0f);
	}
	else
	{
		DoAim(LookAxisVector.X, LookAxisVector.Y);
	}
}

void AUnrealProgramGameCharacter::CrouchInput(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AUnrealProgramGameCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		float YawValue = Yaw;
		float PitchValue = Pitch;

		if (bIsAiming)
		{
			YawValue = Yaw * 0.3f;
			PitchValue = Pitch * 0.3f;
		}

		// pass the rotation inputs
		AddControllerYawInput(YawValue);
		AddControllerPitchInput(PitchValue);
	}
}

void AUnrealProgramGameCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AUnrealProgramGameCharacter::DoJumpStart()
{
	if (PlayerState == EPlayerState::Flying)
	{
		return;
	}

	// pass Jump to the character
	Jump();
}

void AUnrealProgramGameCharacter::DoJumpEnd()
{
	if (PlayerState != EPlayerState::Flying)
	{
		// pass StopJumping to the character
		StopJumping();
	}
}

void AUnrealProgramGameCharacter::DoChargedJumpStart(const FInputActionValue& Value)
{
	if (PlayerState == EPlayerState::Flying)
	{
		return;
	}

	if (!AttributeSet || AttributeSet->GetStamina() < ChargedJumpStaminaCost)
	{
		return;
	}

	GetCharacterMovement()->JumpZVelocity = MaxChargedJumpVelocity;
	Jump();

	AttributeSet->SetStamina(AttributeSet->GetStamina() - ChargedJumpStaminaCost);

	if (ChargedJumpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ChargedJumpSound, GetActorLocation());
	}
}

void AUnrealProgramGameCharacter::DoChargedJumpEnd(const FInputActionValue& Value)
{
	if (PlayerState == EPlayerState::Flying)
	{
		return;
	}

	GetCharacterMovement()->JumpZVelocity = MaxJumpVelocity;
	StopJumping();
}

UAbilitySystemComponent* AUnrealProgramGameCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUnrealProgramGameCharacter::RotateInput(const FInputActionInstance& Instance)
{

	float AxisValue = Instance.GetValue().Get<float>();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::White, FString::Printf(TEXT("Value: %f"), AxisValue));
	}

	if (GetController() && AxisValue != 0.0f)
	{
		float DeltaYaw = AxisValue * 50.0f * GetWorld()->GetDeltaSeconds();

		FRotator CurrentRotation = GetController()->GetControlRotation();
		CurrentRotation.Yaw += DeltaYaw;

		GetController()->SetControlRotation(CurrentRotation);
	}
}

void AUnrealProgramGameCharacter::RotateTriggerOngoing(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Green, FString::Printf(TEXT("Ongoing: %f"), Instance.GetElapsedTime()));
	}
}
void AUnrealProgramGameCharacter::RotateTriggerTriggered(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Blue, FString::Printf(TEXT("Triggered: %f"), Instance.GetTriggeredTime()));
	}
}

void AUnrealProgramGameCharacter::TriggerStateTestStarted(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("TriggerStatesAction Started!"));
	}
}

void AUnrealProgramGameCharacter::TriggerStateTestCompleted(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("TriggerStatesAction Completed!"));
	}
}

void AUnrealProgramGameCharacter::TriggerStateTestCanceled(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("TriggerStatesAction Canceled!"));
	}
}

void AUnrealProgramGameCharacter::TriggerStateTestTriggered(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("TriggerStatesAction Triggered: %f"), Instance.GetTriggeredTime()));
	}
}

void AUnrealProgramGameCharacter::TriggerStateTestOngoing(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, FString::Printf(TEXT("TriggerStatesAction Ongoing: %f"), Instance.GetElapsedTime()));
	}
}

void AUnrealProgramGameCharacter::TriggerQualifierStarted(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Started!"));
	}
}

void AUnrealProgramGameCharacter::TriggerQualifierCompleted(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Completed!"));
	}
}

void AUnrealProgramGameCharacter::TriggerQualifierCanceled(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Canceled!"));
	}
}

void AUnrealProgramGameCharacter::TriggerQualifierTriggered(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("Triggered: %f"), Instance.GetTriggeredTime()));
	}
}

void AUnrealProgramGameCharacter::TriggerQualifierOngoing(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, FString::Printf(TEXT("Ongoing: %f"), Instance.GetElapsedTime()));
	}
}
