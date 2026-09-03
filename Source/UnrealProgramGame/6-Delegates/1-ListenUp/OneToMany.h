#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "OneToMany.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROGRAMGAME_API AOneToMany : public ABaseActor
{
	GENERATED_BODY()

public:
	AOneToMany();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OneToMany")
	TObjectPtr<UBoxComponent> Box;

	UFUNCTION()
	void OnOverlapBeginOne(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBeginTwo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};