// abyrax - 2d project


#include "CharacterGameComponent.h"

#include "Character2D.h"
#include "EnemyBase.h"
#include "PlayerStatWidget.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterGameComponent::UCharacterGameComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterGameComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	CurrentCharacter= Cast<ACharacter2D>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	/*if(Owner && CurrentCharacter)
	{
		RespawnLocation = Owner->GetActorLocation();
	}*/

	if(PlayerStatWidgetClass)
	{
		PlayerStatWidget = NewObject<UPlayerStatWidget>(this, PlayerStatWidgetClass);
		PlayerStatWidget->AddToViewport();
	}
	
}


// Called every frame
void UCharacterGameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterGameComponent::MoveLeftRight(const FInputActionValue& Value)
{
	if(CurrentCharacter && Value.GetMagnitude() != 0.f)
	{
		FVector WorldDirection = FVector(1.f,0.f,0.f);
		CurrentCharacter->AddMovementInput(WorldDirection,Value.GetMagnitude(),false);
	}
	
}

void UCharacterGameComponent::MoveUpDown(const FInputActionValue& Value)
{
	if(CurrentCharacter && Value.GetMagnitude() != 0.f)
	{
		FVector WorldDirection = FVector(0.f,0.f,1.f);
		CurrentCharacter->AddMovementInput(WorldDirection,Value.GetMagnitude(),false);
	}
}

void UCharacterGameComponent::Jump()
{
	bJumping=true;
}

float UCharacterGameComponent::IncrementCollectible()
{
	collectible +=1;
	return collectible;
}

void UCharacterGameComponent::CapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	EnemyBase = Cast<AEnemyBase>(AEnemyBase::StaticClass());
	
	if(EnemyBase)
	{
		if(EnemyBase->CanTakeDamage() && EnemyBase == OtherActor)
		{
			const FVector CurrentActorLocation = CurrentCharacter->GetActorLocation();
			const FVector CapsuleHitLocation = Hit.Location;

			FVector HitDirection = CapsuleHitLocation - CurrentActorLocation;
			HitDirection = HitDirection.GetSafeNormal(0.0f);

			if(HitDirection.Z <= -0.3f)
			{
				EnemyBase->TakeDamage(DefaultDamageAmount,FDamageEvent(),nullptr,nullptr);
			}
			else
			{
				CurrentCharacter->TakeDamage(EnemyBase->GetDamageAmount(),FDamageEvent(),nullptr,nullptr);
			}
		}
	}
}

