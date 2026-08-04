#include "CountDownBomb.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"

ACountDownBomb::ACountDownBomb()
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForce"));
	ExplosionForce->SetupAttachment(RootComp);

	ExplosionForce->Radius = 500.0f;
	ExplosionForce->ImpulseStrength = 2000.0f;
	ExplosionForce->bImpulseVelChange = true;
	ExplosionForce->Falloff = RIF_Linear;
}

void ACountDownBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorldTimerManager().IsTimerActive(BombTimer))
		GEngine->AddOnScreenDebugMessage(13, 1.0f, FColor::Red, FString::Printf(TEXT("Bomb ticking remaining time: %f"), GetWorldTimerManager().GetTimerRemaining(BombTimer)));
}

void ACountDownBomb::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(BombTimer, this, &ACountDownBomb::BombTimerCallback, BombTimerDuration);
}

void ACountDownBomb::BombTimerCallback()
{
	GetWorldTimerManager().ClearTimer(BombTimer);

	GEngine->AddOnScreenDebugMessage(14, 5.0f, FColor::Red, FString::Printf(TEXT("BOOM!!!")));

	if (BombSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BombSound, GetActorLocation());
	}

	if (BombEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BombEffect, GetActorLocation());
	}

	ExplosionForce->FireImpulse();

	Destroy();
}