
#include "TimerDelegate.h"

#include "Components/BoxComponent.h"

ATimerDelegate::ATimerDelegate()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetLineThickness(1.0f);
	Box->SetHiddenInGame(false);
	SetRootComponent(Box);
}

void ATimerDelegate::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATimerDelegate::OnOverlapBegin);
}

void ATimerDelegate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Log(FString::Printf(TEXT("Starting timer for 3.0 seconds!")));

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ATimerDelegate::HandleTimer, GetWorld()->GetTimeSeconds());

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.0f, false);
}

void ATimerDelegate::HandleTimer(const double WorldTime)
{
	Log(FString::Printf(TEXT("Time was: %f when the timer started, time is now: %f"), WorldTime, GetWorld()->GetTimeSeconds()));
}
