// abyrax - 2d project


#include "SpikeInteraction.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

ASpikeInteraction::ASpikeInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void ASpikeInteraction::ChangeSpikeStatus()
{
	bSpikeUp = !bSpikeUp;

	if(bSpikeUp)
	{
		ActivateSpike();
	}
	else
	{
		DeactivateSpike();
	}
}

void ASpikeInteraction::ActivateSpike()
{
	if(SpriteSpikeUp)
	{
		PaperSprite->SetSprite(SpriteSpikeUp);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ASpikeInteraction::DeactivateSpike()
{
	if(SpriteSpikeDown)
	{
		PaperSprite->SetSprite(SpriteSpikeDown);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASpikeInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ASpikeInteraction::BoxBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &ASpikeInteraction::ChangeSpikeStatus,Duration,bLooping);
}

void ASpikeInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PlayerCharacter == OtherActor)
	{
		PlayerCharacter->TakeDamage(DamageAmount,FDamageEvent(),nullptr,nullptr);
		
	}
}
