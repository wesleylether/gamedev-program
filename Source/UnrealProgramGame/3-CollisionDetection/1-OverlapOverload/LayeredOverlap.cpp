#include "LayeredOverlap.h"

#include "Components/SphereComponent.h"

ALayeredOverlap::ALayeredOverlap()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphere->SetupAttachment(SceneComponent);
	InnerSphere->SetLineThickness(3.0f);
	InnerSphere->SetSphereRadius(100.0f);
	InnerSphere->SetHiddenInGame(false);

	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphere->SetupAttachment(SceneComponent);
	OuterSphere->SetLineThickness(3.0f);
	OuterSphere->SetSphereRadius(500.0f);
	OuterSphere->SetHiddenInGame(false);
}

void ALayeredOverlap::BeginPlay()
{
	Super::BeginPlay();

	if (!InnerSphere || !OuterSphere)
		return;

	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereBeginOverlap);
	InnerSphere->OnComponentEndOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereEndOverlap);

	OuterSphere->OnComponentBeginOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereBeginOverlap);
	OuterSphere->OnComponentEndOverlap.AddDynamic(this, &ALayeredOverlap::HandleSphereEndOverlap);
}

void ALayeredOverlap::HandleSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == OuterSphere)
	{
		Message(TEXT("You are getting close!"), -1, 5.0f, FColor::Yellow);
	}
	else if (OverlappedComponent == InnerSphere)
	{
		Message(TEXT("You are right next to me!"), -1, 5.0f, FColor::Red);
	}
}

void ALayeredOverlap::HandleSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent == InnerSphere)
	{
		Message(TEXT("You are further away!"), -1, 5.0f, FColor::Yellow);
	}
	else if (OverlappedComponent == OuterSphere)
	{
		Message(TEXT("I don't see you anymore!"), -1, 5.0f, FColor::Green);
	}
}
