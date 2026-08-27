#pragma once

#include "AbstractClasses/BaseOverlapActor.h"
#include "CoreMinimal.h"

#include "OnlyPlayerOverlap.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API AOnlyPlayerOverlap : public ABaseOverlapActor
{
	GENERATED_BODY()

public:
	AOnlyPlayerOverlap();
};