#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "LandingJudge.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ALandingJudge : public ABaseActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnCharacterLanded(const FHitResult& Hit);
};