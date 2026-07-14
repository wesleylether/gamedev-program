#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UnrealProgramAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class UNREALPROGRAMGAME_API UUnrealProgramAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UUnrealProgramAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UUnrealProgramAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UUnrealProgramAttributeSet, MaxStamina)

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
