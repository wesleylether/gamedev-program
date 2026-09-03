// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeInsideOverlap.h"

void ATimeInsideOverlap::HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TimeStarted = GetWorld()->GetTimeSeconds();
}

void ATimeInsideOverlap::HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const float TimeInside = GetWorld()->GetTimeSeconds() - TimeStarted;

	Message(FString::Printf(TEXT("Time inside: %f"), TimeInside), -1, 4.0f, FColor::Yellow);
}