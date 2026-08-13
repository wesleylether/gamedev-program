#include "ImpactPoint.h"

void AImpactPoint::BeginPlay()
{
	Super::BeginPlay();

	if (!Mesh)
		return;

	Mesh->OnComponentHit.AddDynamic(this, &AImpactPoint::OnHit);
}

void AImpactPoint::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);
	DrawDebugDirectionalArrow(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + Hit.ImpactNormal * 30.0f * -1.0f, 3.0f, FColor::Yellow, false, 2.0f, 0, 1.0f);
}
