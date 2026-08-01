// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeInsideOverlap.h"

void ATimeInsideOverlap::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Super::HandleBoxComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	TimeStarted = GetWorld()->GetTimeSeconds();
}

void ATimeInsideOverlap::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Super::HandleBoxComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	const float TimeInside = GetWorld()->GetTimeSeconds() - TimeStarted;

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Time inside: %f"), TimeInside));
}