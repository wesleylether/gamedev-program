// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProgramGameCharacter.h"
#include "AbilitySystem/Abilities/ChargedJumpAbility.h"
#include "AbilitySystem/Abilities/DashAbility.h"
#include "AbilitySystem/Abilities/FlyAbility.h"
#include "AbilitySystem/Abilities/RunAbility.h"
#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "AbilitySystem/Effects/StaminaGainEffect.h"
#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "TimerManager.h"
#include "UnrealProgramGame.h"
#include "UnrealProgramGamePlayerController.h"

// -------------------------------------------------------------------------
// Core & Initialization
// -------------------------------------------------------------------------

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
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AttributeSet"));

	PrimaryActorTick.bCanEverTick = true;

	// Abilities
	DefaultAbilities.Add(UDashAbility::StaticClass());
	DefaultAbilities.Add(URunAbility::StaticClass());
	DefaultAbilities.Add(UFlyAbility::StaticClass());
	DefaultAbilities.Add(UChargedJumpAbility::StaticClass());

	// Effects
	DefaultEffects.Add(UStaminaGainEffect::StaticClass());
}

void AUnrealProgramGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttributeSet)
	{
		float MaxStamina = AttributeSet->GetMaxStamina();

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

void AUnrealProgramGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::MoveInput);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::MoveInput);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AUnrealProgramGameCharacter::MoveInput);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::WalkInputTriggered);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RunInputTriggered);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::CrouchInput);

		// Jumping & Dashing
		// EnhancedInputComponent->BindAction(DashedAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::DashedStarted);
		EnhancedInputComponent->BindAction(DashedAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DashedTriggered);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DoChargedJumpStart);

		// Flying
		EnhancedInputComponent->BindAction(FlyModeAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::FlyInput);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::FlyUp);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::FlyDown);

		// Looking & Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::LookInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RotateInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::RotateTriggerOngoing);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::RotateTriggerTriggered);
		EnhancedInputComponent->BindAction(TriggerAimAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerAimInputTriggered);
		EnhancedInputComponent->BindAction(TriggerAimAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerAimInputCompleted);
		EnhancedInputComponent->BindAction(TriggerInvertAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerInvertInput);

		// Blueprint Callables for generic Inputs (UI/Controls)
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::DoJumpEnd);

		// Testing / Qualifiers
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::TriggerStateTestStarted);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerStateTestCompleted);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Canceled, this, &AUnrealProgramGameCharacter::TriggerStateTestCanceled);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerStateTestTriggered);
		EnhancedInputComponent->BindAction(TriggerStateTestAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::TriggerStateTestOngoing);

		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Started, this, &AUnrealProgramGameCharacter::TriggerQualifierStarted);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Completed, this, &AUnrealProgramGameCharacter::TriggerQualifierCompleted);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Canceled, this, &AUnrealProgramGameCharacter::TriggerQualifierCanceled);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Triggered, this, &AUnrealProgramGameCharacter::TriggerQualifierTriggered);
		EnhancedInputComponent->BindAction(TriggerQualifierAction, ETriggerEvent::Ongoing, this, &AUnrealProgramGameCharacter::TriggerQualifierOngoing);
	}
	else
	{
		UE_LOG(LogUnrealProgramGame, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// -------------------------------------------------------------------------
// Interfaces
// -------------------------------------------------------------------------

UAbilitySystemComponent* AUnrealProgramGameCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// -------------------------------------------------------------------------
// Engine Overrides
// -------------------------------------------------------------------------

void AUnrealProgramGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GiveAbilities();
		GiveEffects();
	}

	DefaultCameraRelativeLocation = FirstPersonCameraComponent->GetRelativeLocation();
	TargetCameraRelativeLocation = DefaultCameraRelativeLocation;
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

// -------------------------------------------------------------------------
// Gameplay Ability System (GAS)
// -------------------------------------------------------------------------

void AUnrealProgramGameCharacter::GiveAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent)
		return;

	for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		if (Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		}
	}
}

void AUnrealProgramGameCharacter::GiveEffects()
{
	if (!HasAuthority() || !AbilitySystemComponent)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& EffectClass : DefaultEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

// -------------------------------------------------------------------------
// Input Handling Functions
// -------------------------------------------------------------------------

// Movement
void AUnrealProgramGameCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();
	LastDashInput2D = MovementVector;

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
	if (!AbilitySystemComponent)
		return;

	if (Value.Get<bool>())
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag::Abilities::Run));
	}
	else
	{
		const FGameplayTagContainer RunTag(GTag::Abilities::Run);
		AbilitySystemComponent->CancelAbilities(&RunTag);
	}
}

void AUnrealProgramGameCharacter::CrouchInput(const FInputActionValue& Value)
{
	if (!AbilitySystemComponent)
		return;

	FGameplayTagContainer ActiveTags;
	ActiveTags.AddTag(GTag::State::Running);
	ActiveTags.AddTag(GTag::State::Jumping);
	ActiveTags.AddTag(GTag::State::Flying);
	if (AbilitySystemComponent->HasAnyMatchingGameplayTags(ActiveTags))
	{
		return;
	}

	if (Value.Get<bool>())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

// Jumping & Dashing
void AUnrealProgramGameCharacter::DashedTriggered(const FInputActionValue& Values)
{
	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag::Abilities::Dash));
}

void AUnrealProgramGameCharacter::DoChargedJumpStart(const FInputActionValue& Value)
{
	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag::Abilities::ChargedJump));
}

// Flying
void AUnrealProgramGameCharacter::FlyInput()
{
	if (!AbilitySystemComponent)
		return;

	FGameplayTagContainer ActiveTags;
	ActiveTags.AddTag(GTag::State::Flying);
	if (!AbilitySystemComponent->HasAnyMatchingGameplayTags(ActiveTags))
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag::Abilities::Fly));
	}
	else
	{
		FGameplayTagContainer CancelTags;
		CancelTags.AddTag(GTag::Abilities::Fly);
		AbilitySystemComponent->CancelAbilities(&CancelTags);
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

// Looking & Aiming
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

// Blueprint Callables for generic Inputs (UI/Controls)
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

// Testing / Qualifiers
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
