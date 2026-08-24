
#include "TraceRadar.h"

ATraceRadar::ATraceRadar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATraceRadar::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
}

void ATraceRadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * TraceDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), TraceEnd, ObjectQueryParams);

	FColor LineColor = FColor::Green;
	FLinearColor MeshColor = FLinearColor::Green;
	if (bHit)
	{
		LineColor = FColor::Red;
		MeshColor = FLinearColor::Red;

		Log(FString::Printf(TEXT("Intruder deteceted!: %s"), *HitResult.GetActor()->GetName()));

		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 10, FColor::Yellow, false, 0.0f, 0, 1.0f);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, LineColor, false, 0.0f, 0, 1.0f);
	DynamicMaterial->SetVectorParameterValue("Color", MeshColor);
}