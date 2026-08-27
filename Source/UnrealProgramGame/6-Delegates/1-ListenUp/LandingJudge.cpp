#include "LandingJudge.h"

#include "Kismet/GameplayStatics.h"
#include "UnrealProgramGameCharacter.h"

void ALandingJudge::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(PlayerCharacter))
	{
		Character->LandedDelegate.AddDynamic(this, &ALandingJudge::OnCharacterLanded);
	}
}

void ALandingJudge::OnCharacterLanded(const FHitResult& Hit)
{
	Message(FString::Printf(TEXT("Character landed at location: %s, on actor %s"), *Hit.ImpactPoint.ToString(), *Hit.GetActor()->GetName()));
}
