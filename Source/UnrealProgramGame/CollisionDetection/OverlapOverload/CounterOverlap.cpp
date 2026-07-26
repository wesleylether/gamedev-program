// Fill out your copyright notice in the Description page of Project Settings.

#include "CounterOverlap.h"

#include "Components/BoxComponent.h"

ACounterOverlap::ACounterOverlap()
{
	BoxComponent->SetBoxExtent(FVector(64.0f, 256.0f, 64.0f));
}

void ACounterOverlap::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Green, FString::Printf(TEXT("Total actors: %i"), OverlappedActors.Num()));
}

void ACounterOverlap::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BoxComponent->GetOverlappingActors(OverlappedActors);
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Green, FString::Printf(TEXT("Total actors: %i"), OverlappedActors.Num()));
}