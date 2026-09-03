#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "QuestDoor.generated.h"

enum class EQuestTriggerState : uint8;
class UQuestEventSubsystem;

UCLASS()
class UNREALPROGRAMGAME_API AQuestDoor : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	AQuestDoor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestDoor")
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestDoor")
	float DoorSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestGiver")
	FGameplayTag QuestTag;

	UFUNCTION()
	void HandleQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator);

private:
	UPROPERTY()
	TObjectPtr<UQuestEventSubsystem> QuestEventSubsystem;

	bool bIsActivated = false;
	int32 DoorActivatedCount = 0;
	FVector DoorStartLocation;
	FVector DoorEndLocation;
	FVector DoorDestination;
};