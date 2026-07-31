#include "LaunchPad.h"

#include "UnrealProgramGameCharacter.h"

ALaunchPad::ALaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	StaticMesh->OnComponentHit.AddDynamic(this, &ALaunchPad::OnHit);
}

void ALaunchPad::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	FVector LaunchDirection = Hit.ImpactNormal * LaunchVelocity * -1.0f;
	Character->LaunchCharacter(LaunchDirection, true, true);
}
