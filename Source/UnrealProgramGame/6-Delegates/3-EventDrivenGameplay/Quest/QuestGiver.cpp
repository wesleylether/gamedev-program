#include "QuestGiver.h"

#include "AbilitySystem/FGameplayTags.h"
#include "Components/TextRenderComponent.h"
#include "EventSubsystems/QuestEventSubsystem.h"
#include "QuestItem.h"
#include "UnrealProgramGameCustomCollision.h"

AQuestGiver::AQuestGiver()
{
	Mesh->SetCollisionResponseToChannel(ECC_Interact, ECR_Block);

	QuestText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("QuestText"));
	QuestText->SetupAttachment(RootComponent);
	QuestText->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	QuestText->SetText(FText::FromString(""));
	QuestText->SetVisibility(false);
	QuestText->SetHorizontalAlignment(EHTA_Center);
	QuestText->SetWorldSize(40.0f);

	GameplayTags.AddTag(GTag::Interactable::Interact);
}

void AQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	checkf(QuestTag.IsValid(), TEXT("QuestGiver: QuestTag is not set! This is mandatory."));

	QuestEventSubsystem = GetWorld()->GetSubsystem<UQuestEventSubsystem>();
	checkf(QuestEventSubsystem, TEXT("QuestGiver: QuestEventSubsystem is not found!"));

	for (AQuestItem* QuestItem : QuestItems)
	{
		QuestItem->OnQuestItemCollected.AddUniqueDynamic(this, &AQuestGiver::OnQuestItemCollected);
	}
}

void AQuestGiver::Interact_Implementation(APawn* InteractingPawn)
{
	if (bQuestCompleted)
	{
		ShowQuestText(FString(TEXT("Continue with you yourney..")));
		return;
	}

	if (bQuestActive)
	{
		if (QuestItemsCollected < QuestItems.Num())
		{
			ShowQuestText(FString(TEXT("Come back when you collect all the burgers")));
			QuestEventSubsystem->BroadcastQuestState(QuestTag, EQuestTriggerState::Active, QuestItems.Num(), InteractingPawn);
			return;
		}

		bQuestActive = false;
		bQuestCompleted = true;
		ShowQuestText(FString(TEXT("Good work, here is your reward...")));

		QuestEventSubsystem->BroadcastQuestState(QuestTag, EQuestTriggerState::Completed, QuestItems.Num(), InteractingPawn);
		return;
	}

	bQuestActive = true;
	ShowQuestText(FString::Printf(TEXT("Collect %d burgers!"), QuestItems.Num()));

	QuestEventSubsystem->BroadcastQuestState(QuestTag, EQuestTriggerState::Started, QuestItems.Num(), InteractingPawn);
}

void AQuestGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager)
	{
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector TextLocation = QuestText->GetComponentLocation();
		FRotator LookAtRotation = (CameraLocation - TextLocation).Rotation();
		FRotator YawOnlyRotation = FRotator(0.0f, LookAtRotation.Yaw, 0.0f);
		QuestText->SetWorldRotation(YawOnlyRotation);
	}
}

void AQuestGiver::OnQuestItemCollected()
{
	QuestItemsCollected++;

	QuestEventSubsystem->BroadcastQuestItemCollected(QuestTag, QuestItemsCollected, QuestItems.Num());
	Log(FString::Printf(TEXT("Quest Items Collected: %d / %d"), QuestItemsCollected, QuestItems.Num()));
}

void AQuestGiver::ShowQuestText(FString Text)
{
	QuestText->SetText(FText::FromString(Text));
	QuestText->SetVisibility(true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AQuestGiver::HideQuestText, 5.0f, false);
}

void AQuestGiver::HideQuestText()
{
	QuestText->SetVisibility(false);
	QuestText->SetText(FText::FromString(""));
}
