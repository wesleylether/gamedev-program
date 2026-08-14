#include "CountDownBomb.h"

#include "Enum/EScreenMessageKeys.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"

ACountDownBomb::ACountDownBomb()
{
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForce"));
	ExplosionForce->SetupAttachment(GetRootComponent());
	ExplosionForce->Radius = 500.0f;
	ExplosionForce->ImpulseStrength = 2000.0f;
	ExplosionForce->bImpulseVelChange = true;
	ExplosionForce->Falloff = RIF_Linear;
}

void ACountDownBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorldTimerManager().IsTimerActive(BombTimer))
		Message(
			FString::Printf(TEXT("Bomb ticking remaining time: %f"), GetWorldTimerManager().GetTimerRemaining(BombTimer)),
			static_cast<int32>(EScreenMessageKey::Counter),
			1.0f,
			FColor::Red);
}

void ACountDownBomb::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(BombTimer, this, &ACountDownBomb::BombTimerCallback, BombTimerDuration);
}

void ACountDownBomb::BombTimerCallback()
{
	GetWorldTimerManager().ClearTimer(BombTimer);

	Message(FString::Printf(TEXT("BOOM!!!")), static_cast<int32>(EScreenMessageKey::Spawning_Bom), 5.0f, FColor::Red);

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