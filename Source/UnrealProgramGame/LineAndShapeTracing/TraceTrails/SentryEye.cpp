
#include "SentryEye.h"

#include "Components/SphereComponent.h"
#include "Enum/EScreenMessageKeys.h"
#include "Kismet/KismetMathLibrary.h"
#include "UnrealProgramGameCharacter.h"

ASentryEye::ASentryEye()
{
	PrimaryActorTick.bCanEverTick = true;

	VisibilitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("VisibilitySphere"));
	VisibilitySphere->SetSphereRadius(VisibilitySphereRadius);
	VisibilitySphere->SetupAttachment(GetRootComponent());
	VisibilitySphere->SetHiddenInGame(false);
	VisibilitySphere->SetLineThickness(1.0f);
}

void ASentryEye::BeginPlay()
{
	Super::BeginPlay();

	VisibilitySphere->OnComponentBeginOverlap.AddDynamic(this, &ASentryEye::OnOverlapBegin);
	VisibilitySphere->OnComponentEndOverlap.AddDynamic(this, &ASentryEye::OnOverlapEnd);

	if (Mesh->GetMaterial(0))
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
}

void ASentryEye::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
		return;

	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	Target = Character;
	bActivated = true;
}

void ASentryEye::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this)
		return;

	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	Target = nullptr;
	bActivated = false;
}

void ASentryEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bActivated || !Target)
		return;

	const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookRotation, DeltaTime, 5.0f);
	SetActorRotation(NewRotation);

	FVector EndLocation = Target->GetActorLocation();
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), EndLocation, ECC_Visibility, CollisionQueryParams);

	FColor LineColor = FColor::Green;

	if (bHit)
	{

		const AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(HitResult.GetActor());
		if (HitResult.bBlockingHit && Character)
		{
			LineColor = FColor::Red;
			Message(FString::Printf(TEXT("SentryEye: I See you!! %s"), *Target->GetName()), static_cast<int32>(EScreenMessageKey::Trace_Sentry), 0.0f);
		}
		else
		{
			Message(FString::Printf(TEXT("SentryEye: I Don't see you! But what I am seeing is: %s"), *HitResult.GetActor()->GetName()), static_cast<int32>(EScreenMessageKey::Trace_Sentry), 0.0f);
		}
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), EndLocation, LineColor, false, 0.0f, 0, 1.0f);
}
