// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Logging/LogMacros.h"
#include "UnrealProgramGameCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Walking,
	Flying,
};

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UMetaSoundSource;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class AUnrealProgramGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	// Trigger State Tests Module 1-1
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TriggerStateTestAction;

	// Rotate with Q en E Module 1-2.1
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateAction;

	// Slow Aim Module 1-2.2
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TriggerAimAction;

	// Slow Aim Module 1-2.3
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TriggerInvertAction;

	// Trigger Qualifiers
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TriggerQualifierAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* WalkAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ChargedJumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DashedAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FlyModeAction;

public:
	AUnrealProgramGameCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);
	void WalkInputTriggered(const FInputActionValue& Value);
	void RunInputTriggered(const FInputActionValue& Value);

	void DashedStarted(const FInputActionValue& Values);
	void DashedTriggered(const FInputActionValue& Values);
	void StopDash();

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);
	void CrouchInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	void DoChargedJumpStart(const FInputActionValue& Value);

	void DoChargedJumpEnd(const FInputActionValue& Value);

	void RotateInput(const FInputActionInstance& Instance);
	void RotateTriggerOngoing(const FInputActionInstance& InputActionInstance);
	void RotateTriggerTriggered(const FInputActionInstance& InputActionInstance);

	// Trigger State Tests
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

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	void TriggerAimInputTriggered(const FInputActionValue& Value);
	void TriggerAimInputCompleted(const FInputActionValue& Value);
	void TriggerInvertInput(const FInputActionValue& Value);

	void FlyInput();
	void FlyUp();
	void FlyDown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CrouchedCameraOffset = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CameraInterpSpeed = 10.0f;

	FVector DefaultCameraRelativeLocation;
	FVector TargetCameraRelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxSneakSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxWalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxRunSpeed = 1100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxJumpVelocity = 480.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxChargedJumpVelocity = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float DashSpeed = 2500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float DashTiming = 0.35f;

	bool		 bIsAiming = false;
	bool		 bIsInverting = false;
	EPlayerState PlayerState = EPlayerState::Walking;

	FTimerHandle DashTimerHandle;
	FVector2D	 LastDashInput2D;
	FVector2D	 PreviousDashInput2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DashSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ChargedJumpSound;

public:
	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
