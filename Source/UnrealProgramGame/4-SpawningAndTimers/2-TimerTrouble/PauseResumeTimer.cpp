#include "PauseResumeTimer.h"

#include "Components/BoxComponent.h"
#include "Enum/EScreenMessageKeys.h"

APauseResumeTimer::APauseResumeTimer()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(GetRootComponent());
}

void APauseResumeTimer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Message(
		FString::Printf(TEXT("Elapsed Time: %f"), GetWorldTimerManager().GetTimerElapsed(TimerHandle)),
		static_cast<int32>(EScreenMessageKey::TimerTrouble_ElapsedTime),
		1.0f,
		FColor::Yellow);
	Message(
		FString::Printf(TEXT("Is Paused: %s"), bPaused ? TEXT("true") : TEXT("false")),
		static_cast<int32>(EScreenMessageKey::TimerTrouble_Paused),
		1.0f,
		FColor::Yellow);
}

void APauseResumeTimer::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APauseResumeTimer::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APauseResumeTimer::OnOverlapEnd);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APauseResumeTimer::ChangeColor, TimerLength, true);
}

void APauseResumeTimer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bPaused = true;
	GetWorldTimerManager().PauseTimer(TimerHandle);
}

void APauseResumeTimer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bPaused = false;
	GetWorldTimerManager().UnPauseTimer(TimerHandle);
}

void APauseResumeTimer::ChangeColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}
