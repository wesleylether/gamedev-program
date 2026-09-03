#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "LookAndInteract.generated.h"

struct FInputActionValue;
class AUnrealProgramGameCharacter;
class UEnhancedInputComponent;
class UInputAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALPROGRAMGAME_API ULookAndInteract : public UActorComponent
{
	GENERATED_BODY()

public:
	ULookAndInteract();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

protected:
	UPROPERTY(EditAnywhere, Category = "Input|Interaction")
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LookAndInteract")
	float LookDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LookAndInteract")
	float PushImpulseStrength = 100000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LookAndInteract")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LookAndInteract")
	bool bSweepForInteraction = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LookAndInteract")
	float SphereRadius = 20.0f;

	void Input_Interact(const FInputActionValue& Value);

private:
	UPROPERTY()
	TObjectPtr<AUnrealProgramGameCharacter> CharacterOwner;

	FHitResult HitResult;
	void PerformTrace();
};