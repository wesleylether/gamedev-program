
#include "AreaScanner.h"

#include "Engine/OverlapResult.h"
#include "Enum/EScreenMessageKeys.h"

AAreaScanner::AAreaScanner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAreaScanner::BeginPlay()
{
	Super::BeginPlay();
}

void AAreaScanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FOverlapResult> Overlaps;
	const bool bOverlapped = GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(ScanRadius));

	if (bOverlapped && Overlaps.Num() > 0)
	{
		TArray<FString> OverlapNames;
		for (const FOverlapResult& Overlap : Overlaps)
		{
			OverlapNames.Add(Overlap.GetActor()->GetName());
		}

		Message(FString::Join(OverlapNames, TEXT(", ")), static_cast<int32>(EScreenMessageKey::Sweep_AreaScanner), 0.0f);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), ScanRadius, 10, FColor::Red, false, 0.0f);
}
