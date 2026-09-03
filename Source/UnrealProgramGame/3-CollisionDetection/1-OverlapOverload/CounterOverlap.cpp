// Fill out your copyright notice in the Description page of Project Settings.

#include "CounterOverlap.h"

#include "Components/BoxComponent.h"
#include "Enum/EScreenMessageKeys.h"

ACounterOverlap::ACounterOverlap()
{
	BoxComponent->SetBoxExtent(FVector(64.0f, 256.0f, 64.0f));
}

void ACounterOverlap::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
	Message(FString::Printf(TEXT("Total actors: %i"), OverlappedActors.Num()), static_cast<int32>(EScreenMessageKey::Overlap_ActorList), 5.0f);
}

void ACounterOverlap::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
	Message(FString::Printf(TEXT("Total actors: %i"), OverlappedActors.Num()), static_cast<int32>(EScreenMessageKey::Overlap_ActorList), 5.0f);
}