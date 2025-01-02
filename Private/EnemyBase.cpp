// abyrax - 2d project


#include "EnemyBase.h"

#include "Character2D.h"
#include "DeathComponent.h"
#include "HealthComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(GetSprite());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("Death"));
}

void AEnemyBase::ToggleFacingDirection()
{
	if(GetSprite())
	{
		const FVector WorldScale = GetSprite()->K2_GetComponentScale();
		float DirectionValue = 1.0f;
		if(!bEnemyMoveRight)
		{
			DirectionValue = -1.0f;
		}
		const float NewScaleX = FMath::Abs(WorldScale.X) * DirectionValue;
		const FVector NewScale = FVector(NewScaleX, WorldScale.Y, WorldScale.Z);
		GetSprite()->SetWorldScale3D(NewScale);
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ACharacter2D>(UGameplayStatics::GetPlayerCharacter(this,0));
}

void AEnemyBase::BeginDestroy()
{
	Super::BeginDestroy();
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(bCanTakeDamage)
	{
		if(HealthComponent)
		{
			const float UpdatedHealth = HealthComponent->TakeDamage(ActualDamage);
			if(UpdatedHealth == 0)
			{
				Destroy();
			}
		}
	}
	
	
	return ActualDamage;
}

void AEnemyBase::Move()
{
	if(!bFollowing)
	{
		float FacingDirection = 1.0f;
		if(bEnemyMoveRight)
		{
			FacingDirection = -1.0f;
		}
		AddMovementInput(EWorldDirection, FacingDirection);
	}
}

void AEnemyBase::FollowCharacter()
{
	if(PlayerCharacter == nullptr)
	{
		return;
	}
	const FVector EWorldLocation = GetCapsuleComponent()->K2_GetComponentLocation();
	const FVector PWorldLocation = PlayerCharacter->GetCapsuleComponent()->K2_GetComponentLocation();

	const float DiffScale = PWorldLocation.X - EWorldLocation.X;

	if(DiffScale >= 0 && bFollowing)
	{
		if(bFollowing)
		{
			bEnemyMoveRight = false;
		}
	}else
	{
		if(bFollowing)
		{
			bEnemyMoveRight = true;
		}
	}

	ToggleFacingDirection();

	if(FMath::Abs(DiffScale) > MaxDistanceBetweenCharacter)
	{
		AddMovementInput(EWorldDirection,DiffScale);
	}
}
