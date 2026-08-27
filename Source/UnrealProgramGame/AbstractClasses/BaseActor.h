#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"

#include "BaseActor.generated.h"

UCLASS()
class UNREALPROGRAMGAME_API ABaseActor : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ABaseActor();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer GameplayTags;

	bool DebugEnabled() const { return bDebug; }

	void Log(const FString& Message, const ELogVerbosity::Type Verbosity = ELogVerbosity::Warning) const;
	void Message(const FString& Message, const int32 Key = -1, const float TimeToDisplay = 3.0f, const FColor Color = FColor::Green) const;
};