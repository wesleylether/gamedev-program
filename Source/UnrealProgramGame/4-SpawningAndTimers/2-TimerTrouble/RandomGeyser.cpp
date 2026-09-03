#include "RandomGeyser.h"

#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "UnrealProgramGameCharacter.h"

ARandomGeyser::ARandomGeyser()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(GetRootComponent());
}

void ARandomGeyser::BeginPlay()
{
	Super::BeginPlay();

	SetTimer();
}

void ARandomGeyser::SetTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARandomGeyser::Errupt, FMath::FRandRange(2.0f, 10.0f));
}

void ARandomGeyser::Errupt()
{
	TArray<AActor*> ActorArray;
	SphereComp->GetOverlappingActors(ActorArray);

	if (!ActorArray.IsEmpty())
	{
		for (AActor* Actor : ActorArray)
		{
			if (AUnrealProgramGameCharacter* Player = Cast<AUnrealProgramGameCharacter>(Actor))
			{
				Player->LaunchCharacter(FVector::UpVector * EruptionStrength, false, true);
			}
			else
			{
				TArray<UPrimitiveComponent*> Comps;
				Actor->GetComponents<UPrimitiveComponent>(Comps);

				for (UPrimitiveComponent* Comp : Comps)
				{
					if (Comp->IsSimulatingPhysics())
					{
						Comp->AddImpulse(FVector::UpVector * EruptionStrength, NAME_None, true);
						break;
					}
				}
			}
		}
	}

	if (ExplosionFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionFX, GetActorLocation());
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	SetTimer();
}
