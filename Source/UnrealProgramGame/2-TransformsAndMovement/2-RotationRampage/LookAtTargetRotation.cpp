#include "LookAtTargetRotation.h"

#include "Kismet/KismetMathLibrary.h"

void ALookAtTargetRotation::BeginPlay()
{
	Super::BeginPlay();

	if (!TargetActor)
	{
		TargetActor = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}

void ALookAtTargetRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor)
		return;

	const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, LookRotation, DeltaTime, InterpolationSpeed);

	SetActorRotation(SmoothedRotation);
}
