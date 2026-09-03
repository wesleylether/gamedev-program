#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "TownCrierTwo.generated.h"

class ATheTownCrier;
class UTextRenderComponent;

UCLASS()
class UNREALPROGRAMGAME_API ATownCrierTwo : public ABaseMeshActor
{
	GENERATED_BODY()

public:
	ATownCrierTwo();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TownCrierTwo")
	TObjectPtr<UTextRenderComponent> Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TownCrierOne")
	TObjectPtr<ATheTownCrier> TownCrier;

	UFUNCTION()
	void ChangeText();

	TArray<FString> Texts;
};