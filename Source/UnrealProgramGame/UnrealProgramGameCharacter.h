// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Logging/LogMacros.h"
#include "UnrealProgramGameCharacter.generated.h"

// Forward Declarations
class UGameplayAbility;
class UGameplayEffect;
class UPlayerAttributeSet;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UMetaSoundSource;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Walking,
	Flying,
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * A basic first person character
 */
UCLASS(abstract)
class AUnrealProgramGameCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// -------------------------------------------------------------------------
	// Core & Initialization
	// -------------------------------------------------------------------------
	AUnrealProgramGameCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// -------------------------------------------------------------------------
	// Interfaces
	// -------------------------------------------------------------------------
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// -------------------------------------------------------------------------
	// Getters
	// -------------------------------------------------------------------------
	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	float GetMaxWalkSpeed() const { return MaxWalkSpeed; }
	float GetMaxJumpVelocity() const { return MaxJumpVelocity; }

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	FVector2D GetLastDashInput2D() const { return LastDashInput2D; }

	USoundBase* GetChargedJumpSound() const { return ChargedJumpSound; }

protected:
	// -------------------------------------------------------------------------
	// Engine Overrides
	// -------------------------------------------------------------------------
	virtual void BeginPlay() override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	// -------------------------------------------------------------------------
	// Components
	// -------------------------------------------------------------------------
	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPlayerAttributeSet* AttributeSet;

	// -------------------------------------------------------------------------
	// Gameplay Ability System (GAS)
	// -------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	void GiveAbilities();
	void GiveEffects();

	// -------------------------------------------------------------------------
	// Input Actions (Properties)
	// -------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* WalkAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* RunAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* ChargedJumpAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* DashedAction;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	UInputAction* FlyModeAction;

	UPROPERTY(EditAnywhere, Category = "Input|Camera")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input|Camera")
	UInputAction* MouseLookAction;
	UPROPERTY(EditAnywhere, Category = "Input|Camera")
	UInputAction* RotateAction; // Rotate with Q en E Module 1-2.1

	UPROPERTY(EditAnywhere, Category = "Input|Aiming")
	UInputAction* TriggerAimAction; // Slow Aim Module 1-2.2
	UPROPERTY(EditAnywhere, Category = "Input|Aiming")
	UInputAction* TriggerInvertAction; // Slow Aim Module 1-2.3

	UPROPERTY(EditAnywhere, Category = "Input|Testing")
	UInputAction* TriggerStateTestAction; // Trigger State Tests Module 1-1
	UPROPERTY(EditAnywhere, Category = "Input|Testing")
	UInputAction* TriggerQualifierAction; // Trigger Qualifiers

	// -------------------------------------------------------------------------
	// Character Stats & Configuration
	// -------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float MaxSneakSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float MaxWalkSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float MaxRunSpeed = 1100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float MaxJumpVelocity = 480.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float MaxChargedJumpVelocity = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float DashSpeed = 2500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	float DashTiming = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
	float CrouchedCameraOffset = 80.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
	float CameraInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float ChargedJumpStaminaCost = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DashSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ChargedJumpSound;

	// -------------------------------------------------------------------------
	// Input Handling Functions
	// -------------------------------------------------------------------------

	// Movement
	void MoveInput(const FInputActionValue& Value);
	void WalkInputTriggered(const FInputActionValue& Value);
	void RunInputTriggered(const FInputActionValue& Value);
	void CrouchInput(const FInputActionValue& Value);

	// Jumping & Dashing
	void DashedTriggered(const FInputActionValue& Values);
	void DoChargedJumpStart(const FInputActionValue& Value);

	// Flying
	void FlyInput();
	void FlyUp();
	void FlyDown();

	// Looking & Aiming
	void LookInput(const FInputActionValue& Value);
	void RotateInput(const FInputActionInstance& Instance);
	void RotateTriggerOngoing(const FInputActionInstance& InputActionInstance);
	void RotateTriggerTriggered(const FInputActionInstance& InputActionInstance);
	void TriggerAimInputTriggered(const FInputActionValue& Value);
	void TriggerAimInputCompleted(const FInputActionValue& Value);
	void TriggerInvertInput(const FInputActionValue& Value);

	// Blueprint Callables for generic Inputs (UI/Controls)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAim(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	// Testing / Qualifiers
	void TriggerStateTestStarted(const FInputActionValue& Value);
	void TriggerStateTestCompleted(const FInputActionValue& Value);
	void TriggerStateTestCanceled(const FInputActionValue& Value);
	void TriggerStateTestTriggered(const FInputActionInstance& Instance);
	void TriggerStateTestOngoing(const FInputActionInstance& Instance);

	void TriggerQualifierStarted(const FInputActionValue& Value);
	void TriggerQualifierCompleted(const FInputActionValue& Value);
	void TriggerQualifierCanceled(const FInputActionValue& Value);
	void TriggerQualifierTriggered(const FInputActionInstance& Instance);
	void TriggerQualifierOngoing(const FInputActionInstance& Instance);

private:
	// -------------------------------------------------------------------------
	// Internal State
	// -------------------------------------------------------------------------
	bool bIsAiming = false;
	bool bIsInverting = false;

	EPlayerState PlayerState = EPlayerState::Walking;

	FVector DefaultCameraRelativeLocation;
	FVector TargetCameraRelativeLocation;

	FTimerHandle DashTimerHandle;
	FVector2D	 LastDashInput2D;
	FVector2D	 PreviousDashInput2D;
};