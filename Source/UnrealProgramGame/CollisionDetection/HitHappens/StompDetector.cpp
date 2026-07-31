#include "StompDetector.h"

#include "GameFramework/Character.h"

AStompDetector::AStompDetector()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStompDetector::BeginPlay()
{
	Super::BeginPlay();

	if (!StaticMesh)
		return;

	if (StaticMesh->GetMaterial(0))
	{
		DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	StaticMesh->OnComponentHit.AddDynamic(this, &AStompDetector::OnHit);
}

void AStompDetector::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter || !PlayerCharacter->IsPlayerControlled())
		return;

	if (FMath::Abs(Hit.ImpactNormal.Z) < MinStompZNormal)
		return;

	UE_LOG(LogTemp, Warning, TEXT("STOMPED!"));

	ApplyRandomColor();
}

void AStompDetector::ApplyRandomColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}
