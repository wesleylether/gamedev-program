#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "QuestItem.generated.h"

class UNiagaraSystem;
class USphereComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuestItemCollectedDelegate);

UCLASS()
class UNREALPROGRAMGAME_API AQuestItem : public ABaseActor
{
	GENERATED_BODY()

public:
	AQuestItem();

	UPROPERTY(BlueprintAssignable)
	FQuestItemCollectedDelegate OnQuestItemCollected;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<USoundBase> CollectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestItem")
	TObjectPtr<UNiagaraSystem> CollectEffect;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};