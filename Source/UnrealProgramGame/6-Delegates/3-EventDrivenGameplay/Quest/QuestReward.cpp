#include "QuestReward.h"

#include "EventSubsystems/QuestEventSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

void AQuestReward::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);

	checkf(QuestTag.IsValid(), TEXT("QuestGiver: QuestTag is not set! This is mandatory."));

	QuestEventSubsystem = GetWorld()->GetSubsystem<UQuestEventSubsystem>();
	checkf(QuestEventSubsystem, TEXT("QuestGiver: QuestEventSubsystem is not found!"));

	QuestEventSubsystem->OnQuestStateChanged.AddUniqueDynamic(this, &AQuestReward::HandleQuestEvent);
}

void AQuestReward::Interact_Implementation(APawn* InteractingPawn)
{
	if (CollectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
	}

	if (CollectEffect)
	{
		UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CollectEffect, GetActorLocation());
		if (SpawnedEffect)
		{
			SpawnedEffect->SetAutoDestroy(true);
		}
	}

	Super::Interact_Implementation(InteractingPawn);
}

void AQuestReward::HandleQuestEvent(FGameplayTag Tag, EQuestTriggerState State, int32 ItemsTotal, AActor* EventInstigator)
{
	if (Tag != QuestTag)
		return;

	if (State != EQuestTriggerState::Completed)
		return;

	SetActorHiddenInGame(false);
}
