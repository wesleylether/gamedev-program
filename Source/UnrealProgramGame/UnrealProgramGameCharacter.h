// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Logging/LogMacros.h"
#include "UnrealProgramGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;

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

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

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

public:
	AUnrealProgramGameCharacter();

protected:
	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

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

	void RotateInput(const FInputActionInstance& Instance);
	void RotateTriggerOngoing(const FInputActionInstance& InputActionInstance);
	void RotateTriggerTriggered(const FInputActionInstance& InputActionInstance);

	// Trigger State Tests
	void TriggerStateTestStarted(const FInputActionValue& Value);
	void TriggerStateTestCompleted(const FInputActionValue& Value);
	void TriggerStateTestCanceled(const FInputActionValue& Value);
	void TriggerStateTestTriggered(const FInputActionInstance& Instance);
	void TriggerStateTestOngoing(const FInputActionInstance& Instance);

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	void TriggerAimInputTriggered(const FInputActionValue& Value);
	void TriggerAimInputCompleted(const FInputActionValue& Value);
	void TriggerInvertInput(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CrouchedCameraOffset = 80.0f;

	bool bIsAiming = false;
	bool bIsInverting = false;

public:
	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
