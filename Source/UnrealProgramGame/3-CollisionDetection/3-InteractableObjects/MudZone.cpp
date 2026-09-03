#include "MudZone.h"

#include "AbilitySystem/FGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealProgramGameCharacter.h"

AMudZone::AMudZone()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

void AMudZone::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMudZone::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMudZone::OnOverlapEnd);
}

void AMudZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
	if (!ASC)
		return;

	// todo: create nice InMudEffect
	Character->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	Character->GetCharacterMovement()->JumpZVelocity = 0.0f;
	ASC->AddLooseGameplayTag(GTag::State::InMud);
}

void AMudZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnrealProgramGameCharacter* Character = Cast<AUnrealProgramGameCharacter>(OtherActor);
	if (!Character)
		return;

	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
	if (!ASC)
		return;

	// todo: create nice InMudEffect
	ASC->RemoveLooseGameplayTag(GTag::State::InMud);
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxWalkSpeed();
	Character->GetCharacterMovement()->JumpZVelocity = Character->GetMaxJumpVelocity();
}
