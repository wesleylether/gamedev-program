#include "BaseActor.h"

ABaseActor::ABaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseActor::Log(const FString& Message, const ELogVerbosity::Type Verbosity) const
{
	if (!bDebug)
		return;

	switch (Verbosity)
	{
		case ELogVerbosity::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
			break;
		case ELogVerbosity::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
			break;
		case ELogVerbosity::Display:
			UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
			break;
		case ELogVerbosity::Log:
			UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
			break;
		case ELogVerbosity::Verbose:
			UE_LOG(LogTemp, Verbose, TEXT("%s"), *Message);
			break;
		case ELogVerbosity::VeryVerbose:
			UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *Message);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
			break;
	}
}

void ABaseActor::Message(const FString& Message, const int32 Key, const float TimeToDisplay, const FColor Color) const
{
	if (!bDebug)
		return;

	if (!GEngine)
		return;

	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, Color, Message);
}