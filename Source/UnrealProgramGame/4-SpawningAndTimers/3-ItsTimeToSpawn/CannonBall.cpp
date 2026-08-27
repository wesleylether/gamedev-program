#include "CannonBall.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "UnrealProgramGameCharacter.h"

ACannonBall::ACannonBall()
{

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetSphereRadius(60.0f);

	CannonBallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBallMeshComponent"));
	CannonBallMeshComponent->SetupAttachment(CollisionComponent);

	CannonBallEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CannonBallEffect"));
	CannonBallEffect->SetupAttachment(CollisionComponent);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForce"));
	ExplosionForce->SetupAttachment(CollisionComponent);
	ExplosionForce->Radius = ExplosionRadius;
	ExplosionForce->ImpulseStrength = CannonBallPower;
	ExplosionForce->bImpulseVelChange = true;
	ExplosionForce->Falloff = RIF_Linear;

	CannonBallExplosionEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CannonBallExplosionEffect"));
	CannonBallExplosionEffect->SetupAttachment(CollisionComponent);
	CannonBallExplosionEffect->bAutoActivate = false;
}

void ACannonBall::LaunchCannonBall(const FVector& LaunchDirection, float LaunchStrength)
{
	if (CollisionComponent && CollisionComponent->IsSimulatingPhysics())
	{
		CollisionComponent->AddImpulse(LaunchDirection * LaunchStrength, NAME_None, true);
	}
}

void ACannonBall::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACannonBall::OnHit);

	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ACannonBall::Explode, CannonBallLifeTime, false);
}

void ACannonBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHasExploded)
		return;

	if (OtherActor == GetOwner())
		return;

	if (bOnlyHitActors)
	{
		AActor* Actor = Cast<AActor>(OtherActor);
		if (Actor)
		{
			Explode();
		}
	}
	else
	{
		Explode();
	}
}

void ACannonBall::Explode()
{
	if (bHasExploded)
		return;

	bHasExploded = true;

	GetWorldTimerManager().ClearTimer(LifeTimerHandle);

	FVector ExplodeLocation = GetActorLocation();
	FHitResult GroundHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector TraceStart = ExplodeLocation;
	FVector TraceEnd = ExplodeLocation + FVector(0.0f, 0.0f, -1000.0f);
	if (GetWorld()->LineTraceSingleByChannel(GroundHit, TraceStart, TraceEnd, ECC_Visibility, Params))
	{
		ExplodeLocation = GroundHit.Location;
	}

	SetActorLocation(ExplodeLocation);

	if (CollisionComponent)
	{
		CollisionComponent->SetSimulatePhysics(false);
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (CannonBallEffect)
	{
		CannonBallEffect->Deactivate();
	}

	if (CannonBallMeshComponent)
	{
		CannonBallMeshComponent->DestroyComponent();
	}

	if (ExplosionForce)
	{
		ExplosionForce->SetWorldLocation(ExplodeLocation);
		ExplosionForce->FireImpulse();
	}

	if (CannonBallExplosionEffect)
	{
		CannonBallExplosionEffect->Activate(true);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, ExplodeLocation);
	}

	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ACannonBall::OnExplosionFinished, ExplosionEffectLifetime, false);
}

void ACannonBall::OnExplosionFinished()
{
	Destroy();
}
