#include "BaseOverlapActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

ABaseOverlapActor::ABaseOverlapActor()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComp);
	BoxComponent->SetLineThickness(3.0f);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetBoxExtent(FVector(64.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));
	BoxComponent->SetHiddenInGame(false);

	PrimaryActorTick.bCanEverTick = false;
}

void ABaseOverlapActor::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseOverlapActor::HandleBoxComponentBeginOverlap);
		BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseOverlapActor::HandleBoxComponentEndOverlap);
	}
}

void ABaseOverlapActor::HandleBoxComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor*				 OtherActor,
	UPrimitiveComponent* OtherComp,
	int32				 OtherBodyIndex,
	bool				 bFromSweep,
	const FHitResult&	 SweepResult)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
	{
		return;
	}

	PrintOverlapMessage(TEXT("Overlap Begin"), OtherActor, OtherComp);
}

void ABaseOverlapActor::HandleBoxComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor*				 OtherActor,
	UPrimitiveComponent* OtherComp,
	int32				 OtherBodyIndex)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
	{
		return;
	}

	PrintOverlapMessage(TEXT("Overlap End"), OtherActor, OtherComp);
}

void ABaseOverlapActor::PrintOverlapMessage(const FString& EventName, const AActor* OtherActor, const UPrimitiveComponent* OtherComp)
{
	const FString Message = FString::Printf(TEXT("%s: %s | %s"), *EventName, *GetNameSafe(OtherActor), *GetNameSafe(OtherComp));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Message);
}