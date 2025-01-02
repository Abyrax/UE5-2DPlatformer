// abyrax - 2d project


#include "JumperInteraction.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

AJumperInteraction::AJumperInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void AJumperInteraction::BeginPlay()
{
	Super::BeginPlay();
	if(BoxComponent){
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AJumperInteraction::BoxBeginOverlap);
	}
}

void AJumperInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PlayerCharacter==nullptr)
	{
		return;
	}
	if(OtherActor==PlayerCharacter && (OtherActor != this))
	{
		PlayerCharacter->LaunchCharacter(LaunchVelocity,false,true);
		if(SpriteJumperUp)
		{
			PaperSprite->SetSprite(SpriteJumperUp);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AJumperInteraction::ResetJumper,Duration,false);
		}
	}
}

void AJumperInteraction::ResetJumper()
{
	PaperSprite->SetSprite(SpriteJumperDown);
}
