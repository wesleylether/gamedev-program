#pragma once

#include "AbstractClasses/BaseMeshActor.h"
#include "CoreMinimal.h"

#include "RemoteControl.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ARemoteControl : public ABaseMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RemoteControl")
	TObjectPtr<AActor> Target;
};