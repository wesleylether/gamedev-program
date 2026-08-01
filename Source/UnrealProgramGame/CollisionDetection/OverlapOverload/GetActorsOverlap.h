// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CollisionDetection/Base/BaseOverlapActor.h"
#include "CoreMinimal.h"

#include "GetActorsOverlap.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AGetActorsOverlap : public ABaseOverlapActor
{
	GENERATED_BODY()
public:
	AGetActorsOverlap();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void HandleBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void HandleBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> OverlappedActors;
};