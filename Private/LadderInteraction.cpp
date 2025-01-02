// abyrax - 2d project


#include "LadderInteraction.h"

#include "Character2D.h"
#include "CharacterGameComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALadderInteraction::ALadderInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALadderInteraction::BeginPlay()
{
	Super::BeginPlay();
	if(BoxComponent){
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ALadderInteraction::BoxBeginOverlap);
		BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ALadderInteraction::BoxEndOverlap);
	}

	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	if(PlayerController){
		APawn* CurrentCharacter = PlayerController->GetPawn();
		PlayerCharacter = Cast<ACharacter2D>(CurrentCharacter);
	}
}

// Called every frame
void ALadderInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadderInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		if(UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			CharacterGameComponent->SetOnLadder(true);
		}
	}
}

void ALadderInteraction::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

		if(UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			CharacterGameComponent->SetOnLadder(false);
		}
	}
}

