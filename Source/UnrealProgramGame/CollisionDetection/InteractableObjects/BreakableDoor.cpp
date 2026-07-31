#include "BreakableDoor.h"

#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealProgramGameCharacter.h"

ABreakableDoor::ABreakableDoor()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneRootComponent);

	DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshComponent"));
	DoorMeshComponent->SetupAttachment(SceneRootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void ABreakableDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorMeshComponent->OnComponentHit.AddDynamic(this, &ABreakableDoor::OnHit);
}

void ABreakableDoor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			if (bIsBroken)
				return;

			AUnrealProgramGameCharacter* PlayerCharacter = Cast<AUnrealProgramGameCharacter>(OtherActor);
			if (!IsValid(PlayerCharacter))
				return;

			float ImpactSpeed = 0.0f;
			if (UCharacterMovementComponent* MoveComp = PlayerCharacter->GetCharacterMovement())
				ImpactSpeed = MoveComp->GetLastUpdateVelocity().Size();

			if (ImpactSpeed < BreakLimit)
			{
				UE_LOG(LogTemp, Warning, TEXT("Not dashing or impact speed too low"));
				return;
			}

			bIsBroken = true;

			if (DoorMeshComponent)
			{
				DoorMeshComponent->SetSimulatePhysics(true);
				DoorMeshComponent->AddImpulse(FVector(0.0f, -1.0f, 0.0f) * BreakForce, NAME_None, true);
			}
		}
	}
}
