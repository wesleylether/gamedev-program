// Fill out your copyright notice in the Description page of Project Settings.

#include "OnlyPlayerOverlap.h"

#include "Components/BoxComponent.h"

AOnlyPlayerOverlap::AOnlyPlayerOverlap()
{
	BoxComponent->SetBoxExtent(FVector(64.0f, 128.0f, 64.0f));
	BoxComponent->SetCollisionProfileName("OverlapOnlyPawn");
}