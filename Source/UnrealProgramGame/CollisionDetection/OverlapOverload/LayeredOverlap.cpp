#include "LayeredOverlap.h"

#include "Components/SphereComponent.h"

ALayeredOverlap::ALayeredOverlap()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComponent->SetupAttachment(RootComp);
	InnerSphereComponent->SetLineThickness(3.0f);
	InnerSphereComponent->SetSphereRadius(100.0f);
	InnerSphereComponent->SetHiddenInGame(false);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComponent->SetupAttachment(RootComp);
	OuterSphereComponent->SetLineThickness(3.0f);
	OuterSphereComponent->SetSphereRadius(500.0f);
	OuterSphereComponent->SetHiddenInGame(false);
}

void ALayeredOverlap::BeginPlay()
{
	Super::BeginPlay();

	if (!InnerSphereComponent || !OuterSphereComponent)
		return;

	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereBeginOverlap);
	InnerSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereEndOverlap);

	OuterSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereBeginOverlap);
	OuterSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereEndOverlap);
}

void ALayeredOverlap::HandleSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == OuterSphereComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("You are getting close!"));
	}
	else if (OverlappedComponent == InnerSphereComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You are right next to me!"));
	}
}

void ALayeredOverlap::HandleSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent == InnerSphereComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("You are further away!"));
	}
	else if (OverlappedComponent == OuterSphereComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("I don't see you anymore!"));
	}
}
