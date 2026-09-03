#pragma once

#include "5-LineAndShapeTracing/3-LookAndInteract/Interactable.h"
#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "QuestGiver.generated.h"

class UQuestEventSubsystem;
class AQuestItem;
class UTextRenderComponent;

UCLASS()
class UNREALPROGRAMGAME_API AQuestGiver : public ABaseMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	AQuestGiver();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractingPawn) override;

protected:
	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver")
	bool bQuestActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver")
	bool bQuestCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestGiver")
	FGameplayTag QuestTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver")
	TObjectPtr<UTextRenderComponent> QuestText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestGiver")
	TArray<AQuestItem*> QuestItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver")
	int32 QuestItemsCollected = 0;

	UFUNCTION()
	void OnQuestItemCollected();

	void ShowQuestText(FString Text);
	void HideQuestText();

private:
	UPROPERTY()
	TObjectPtr<UQuestEventSubsystem> QuestEventSubsystem;
};