#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "Resident.generated.h"

class ADoorbell;

UCLASS()
class UNREALPROGRAMGAME_API AResident : public ABaseMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Redient")
	TObjectPtr<ADoorbell> Doorbell;

	UFUNCTION()
	void OnDoorbellRung();
};