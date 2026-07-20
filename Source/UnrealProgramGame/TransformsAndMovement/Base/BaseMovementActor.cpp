// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMovementActor.h"

ABaseMovementActor::ABaseMovementActor()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComp);

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseMovementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMovementActor::BeginPlay()
{
	Super::BeginPlay();
}
