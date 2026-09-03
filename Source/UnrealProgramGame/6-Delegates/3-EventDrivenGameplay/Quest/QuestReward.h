#pragma once

#include "AbstractClasses/BaseSpawnObject.h"
#include "CoreMinimal.h"
#include "QuestDoor.h"

#include "QuestReward.generated.h"

class UNiagaraSystem;
class UQuestEventSubsystem;

UCLASS()
class UNREALPROGRAMGAME_API AQuestReward : public ABaseSpawnObject
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InteractingPawn) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestGiver")
	FGameplayTag QuestTag;

	UFUNCTION()
	void HandleQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<USoundBase> CollectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<UNiagaraSystem> CollectEffect;

private:
	UPROPERTY()
	UQuestEventSubsystem* QuestEventSubsystem;
};