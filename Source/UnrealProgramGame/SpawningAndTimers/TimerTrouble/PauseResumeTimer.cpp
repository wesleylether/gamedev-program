#include "PauseResumeTimer.h"

#include "Components/BoxComponent.h"

APauseResumeTimer::APauseResumeTimer()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComp);
}

void APauseResumeTimer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Yellow, FString::Printf(TEXT("Elapsed Time: %f"), GetWorldTimerManager().GetTimerElapsed(TimerHandle)));
	GEngine->AddOnScreenDebugMessage(12, 1.0f, FColor::Yellow, FString::Printf(TEXT("Is Paused: %s"), bPaused ? TEXT("true") : TEXT("false")));
}

void APauseResumeTimer::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

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
