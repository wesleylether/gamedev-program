#include "LayeredOverlap.h"

#include "Components/SphereComponent.h"

ALayeredOverlap::ALayeredOverlap()
{
	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComponent->SetupAttachment(GetRootComponent());
	InnerSphereComponent->SetLineThickness(3.0f);
	InnerSphereComponent->SetSphereRadius(100.0f);
	InnerSphereComponent->SetHiddenInGame(false);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComponent->SetupAttachment(GetRootComponent());
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
		Message(TEXT("You are getting close!"), -1, 5.0f, FColor::Yellow);
	}
	else if (OverlappedComponent == InnerSphereComponent)
	{
		Message(TEXT("You are right next to me!"), -1, 5.0f, FColor::Red);
	}
}

void ALayeredOverlap::HandleSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent == InnerSphereComponent)
	{
		Message(TEXT("You are further away!"), -1, 5.0f, FColor::Yellow);
	}
	else if (OverlappedComponent == OuterSphereComponent)
	{
		Message(TEXT("I don't see you anymore!"), -1, 5.0f, FColor::Green);
	}
}
