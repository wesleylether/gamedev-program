#include "BaseOverlapActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

ABaseOverlapActor::ABaseOverlapActor()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
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
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
	{
		return;
	}

	Message(FString::Printf(TEXT("Overlap Begin: %s | %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp)));
}

void ABaseOverlapActor::HandleBoxComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!OverlappedComponent || !OtherActor || OtherActor == this || !OtherComp)
	{
		return;
	}

	Message(FString::Printf(TEXT("Overlap End: %s | %s"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp)));
}