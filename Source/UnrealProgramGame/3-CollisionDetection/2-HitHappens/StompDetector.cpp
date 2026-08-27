#include "StompDetector.h"

#include "GameFramework/Character.h"

void AStompDetector::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
	{
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	Mesh->OnComponentHit.AddDynamic(this, &AStompDetector::OnHit);
}

void AStompDetector::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter || !PlayerCharacter->IsPlayerControlled())
		return;

	if (FMath::Abs(Hit.ImpactNormal.Z) < MinStompZNormal)
		return;

	Log(FString::Printf(TEXT("STOMPED!")));

	ApplyRandomColor();
}

void AStompDetector::ApplyRandomColor()
{
	if (!IsValid(DynamicMaterial))
		return;

	const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	DynamicMaterial->SetVectorParameterValue("Color", RandomColor);
}
