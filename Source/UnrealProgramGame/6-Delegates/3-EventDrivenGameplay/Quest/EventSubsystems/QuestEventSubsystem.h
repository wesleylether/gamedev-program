// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystem/FGameplayTags.h"
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "QuestEventSubsystem.generated.h"

UENUM(BlueprintType)
enum class EQuestTriggerState : uint8
{
	Started UMETA(DisplayName = "Started"),
	Idle UMETA(DisplayName = "Idle"),
	Active UMETA(DisplayName = "Active"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed"),
	Aborted UMETA(DisplayName = "Aborted"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnQuestStateChangedDelegate, FGameplayTag, Tag, EQuestTriggerState, State, int32, ItemsTotal, AActor*, EventInstigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestItemCollectedDelegate, FGameplayTag, Tag, int32, ItemsCollected, int32, ItemsTotal);

UCLASS()
class UNREALPROGRAMGAME_API UQuestEventSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events|Triggers")
	FOnQuestStateChangedDelegate OnQuestStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events|Quest")
	FOnQuestItemCollectedDelegate OnQuestItemCollected;

	UFUNCTION(BlueprintCallable, Category = "Events|Triggers")
	void BroadcastQuestState(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator) const
	{
		OnQuestStateChanged.Broadcast(Tag, State, ItemsTotal, EventInstigator);
	}

	UFUNCTION(BlueprintCallable, Category = "Events|Quest")
	void BroadcastQuestItemCollected(FGameplayTag Tag, int32 ItemsCollected, int32 ItemsTotal) const
	{
		OnQuestItemCollected.Broadcast(Tag, ItemsCollected, ItemsTotal);
	}
};
