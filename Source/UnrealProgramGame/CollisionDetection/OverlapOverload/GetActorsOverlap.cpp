// Fill out your copyright notice in the Description page of Project Settings.

#include "GetActorsOverlap.h"

#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

AGetActorsOverlap::AGetActorsOverlap()
{
	BoxComponent->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 203.0f));

	PrimaryActorTick.bCanEverTick = true;
}

void AGetActorsOverlap::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FString ActorNames;
	for (int32 i = 0; i < OverlappedActors.Num(); ++i)
	{
		if (OverlappedActors[i])
		{
			if (i > 0)
			{
				ActorNames += TEXT(", ");
			}
			ActorNames += OverlappedActors[i]->GetName();
		}
	}

	if (!ActorNames.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(5, DeltaSeconds, FColor::Orange,
			FString::Printf(TEXT("Overlapped Actors: %s"), *ActorNames));
	}
}

void AGetActorsOverlap::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
}

void AGetActorsOverlap::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
}
