// abyrax - 2d project


#include "CollectibleInteraction.h"

#include "CharacterGameComponent.h"
#include "PaperSpriteComponent.h"
#include "PlayerStatWidget.h"
#include "Components/BoxComponent.h"

ACollectibleInteraction::ACollectibleInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void ACollectibleInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ACollectibleInteraction::BoxBeginOverlap);
}

void ACollectibleInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PlayerCharacter == nullptr)
	{
		return;
	}

	if(OtherActor == PlayerCharacter && (OtherActor != this))
	{
		if(UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			const float CurrenctCollectible = CharacterGameComponent->IncrementCollectible();
			CharacterGameComponent->GetPlayerStatWidget()->UpdateCollectible(CurrenctCollectible);
			Destroy();
		}
	}
}

void ACollectibleInteraction::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
