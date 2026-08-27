#include "DieBox.h"

#include "Components/BoxComponent.h"
#include "UnrealProgramGameCharacter.h"
#include "UnrealProgramGameGameMode.h"
#include "UnrealProgramGamePlayerController.h"

ADieBox::ADieBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 40.0f));
	BoxComponent->SetupAttachment(GetRootComponent());
}

void ADieBox::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADieBox::HandleOverlap);
}

void ADieBox::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor))
	{
		if (AUnrealProgramGamePlayerController* PlayerController = Cast<AUnrealProgramGamePlayerController>(Character->GetController()))
		{
			if (APawn* Pawn = PlayerController->GetPawn())
			{
				Message(TEXT("Player died"), -1, 5.0f, FColor::Red);

				PlayerController->UnPossess();
				Pawn->Destroy();

				if (AUnrealProgramGameGameMode* GameMode = Cast<AUnrealProgramGameGameMode>(GetWorld()->GetAuthGameMode()))
				{
					GameMode->RestartPlayer(PlayerController);
				}
			}
		}
	}
}
