#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "AreaScanner.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AAreaScanner : public ABaseActor
{
	GENERATED_BODY()

public:
	AAreaScanner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AreaScanner")
	float ScanRadius = 300.0f;
};