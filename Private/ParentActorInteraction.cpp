// abyrax - 2d project


#include "ParentActorInteraction.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"

// Sets default values
AParentActorInteraction::AParentActorInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("sprite"));
	RootComponent = PaperSprite;
}

// Called when the game starts or when spawned
void AParentActorInteraction::BeginPlay()
{
	Super::BeginPlay();
	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	if(PlayerController){
	APawn* CurrentCharacter = PlayerController->GetPawn();
	PlayerCharacter = Cast<ACharacter2D>(CurrentCharacter);
	}
}

// Called every frame
void AParentActorInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

