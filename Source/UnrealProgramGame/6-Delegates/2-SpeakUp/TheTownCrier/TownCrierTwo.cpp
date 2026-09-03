
#include "TownCrierTwo.h"

#include "6-Delegates/2-SpeakUp/TheTownCrier.h"
#include "Components/TextRenderComponent.h"

ATownCrierTwo::ATownCrierTwo()
{
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(GetRootComponent());
	Text->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetVerticalAlignment(EVRTA_TextCenter);

	Texts.Add(TEXT("Amet reprehenderit quis irure."));
	Texts.Add(TEXT("Irure pariatur culpa sunt occaecat veniam ex."));
	Texts.Add(TEXT("Veniam minim cillum ut esse tempor non enim laborum ad elit sit ullamco ex id minim."));
	Texts.Add(TEXT("Duis ea consequat excepteur laborum commodo laborum voluptate esse laborum."));
	Texts.Add(TEXT("Et laborum proident enim consectetur sint officia fugiat eu laborum."));
}

void ATownCrierTwo::BeginPlay()
{
	Super::BeginPlay();

	if (!TownCrier)
		return;

	TownCrier->OnSpeakUp.AddUniqueDynamic(this, &ATownCrierTwo::ChangeText);
}

void ATownCrierTwo::ChangeText()
{
	const int32 RandomIndex = FMath::RandRange(0, Texts.Num() - 1);
	Text->SetText(FText::FromString(Texts[RandomIndex]));
}
