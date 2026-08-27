#include "LookAndInteract.h"

#include "AbilitySystem/FGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagAssetInterface.h"
#include "Interactable.h"
#include "UI/MyMainDashboard.h"
#include "UnrealProgramGameCharacter.h"
#include "UnrealProgramGameCustomCollision.h"

ULookAndInteract::ULookAndInteract()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULookAndInteract::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<AUnrealProgramGameCharacter>(GetOwner());
}

void ULookAndInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformTrace();
}

void ULookAndInteract::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
		return;

	if (!InteractionAction)
		return;

	EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ULookAndInteract::Input_Interact);
}

void ULookAndInteract::Input_Interact(const FInputActionValue& Value)
{
	if (!HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to interact with"));
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
		return;

	IGameplayTagAssetInterface* GameplayTagInterface = Cast<IGameplayTagAssetInterface>(HitActor);

	if (GameplayTagInterface && GameplayTagInterface->HasMatchingGameplayTag(GTag::Interactable::Any))
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s"), *HitResult.GetActor()->GetName());
		CharacterOwner->GetMainDashboard()->HighlightPrompt(FString::Printf(TEXT("%s"), *HitActor->GetName()), 2.0f, FLinearColor::Green);

		if (GameplayTagInterface->HasMatchingGameplayTag(GTag::Interactable::Pickup))
		{
			if (HitActor->Implements<UInteractable>())
				IInteractable::Execute_Interact(HitActor, CharacterOwner);
		}

		if (GameplayTagInterface->HasMatchingGameplayTag(GTag::Interactable::Push))
		{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			if (HitComponent && HitComponent->IsSimulatingPhysics())
			{
				FVector ImpulseDirection = CharacterOwner->GetActorForwardVector();
				HitComponent->AddImpulseAtLocation(ImpulseDirection * PushImpulseStrength, HitResult.ImpactPoint);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't interact with: %s"), *HitResult.GetActor()->GetName());
		CharacterOwner->GetMainDashboard()->HighlightPrompt(FString::Printf(TEXT("Can't interact with: %s"), *HitActor->GetName()), 1.0f, FLinearColor::Yellow);
	}
}

void ULookAndInteract::PerformTrace()
{
	if (!CharacterOwner || !GetWorld())
		return;

	FVector CameraLocation;
	FRotator CameraRotation;

	CharacterOwner->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	const FVector TraceStart = CameraLocation;
	const FVector TraceEnd = CameraLocation + CameraRotation.Vector() * LookDistance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(CharacterOwner);

	if (bSweepForInteraction)
	{
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);
		GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_Interact, CollisionShape, CollisionQueryParams);
	}
	else
	{
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Interact, CollisionQueryParams);
	}

	if (HitResult.bBlockingHit)
	{
		CharacterOwner->GetMainDashboard()->ShowCrossHair(true);

		AActor* Actor = HitResult.GetActor();
		IGameplayTagAssetInterface* GameplayTagInterface = Cast<IGameplayTagAssetInterface>(Actor);
		const bool bCanInteract = GameplayTagInterface && GameplayTagInterface->HasMatchingGameplayTag(GTag::Interactable::Any);
		CharacterOwner->GetMainDashboard()->ShowPrompt(bCanInteract);
	}
	else
	{
		CharacterOwner->GetMainDashboard()->ShowCrossHair(false);
		CharacterOwner->GetMainDashboard()->ShowPrompt(false);
	}

	if (!bDebug)
		return;

	if (bSweepForInteraction)
	{
		if (HitResult.bBlockingHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 10, FColor::Cyan, false, 0.0f, 0, 1.0f);
			DrawDebugSphere(GetWorld(), HitResult.Location, SphereRadius, 10, FColor::Red, false, 0.0f, 0, 1.0f);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, HitResult.bBlockingHit ? FColor::Green : FColor::Red, false, 0.0f, 0, 1.0f);
	}
}
