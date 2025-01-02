// abyrax - 2d project


#include "Character2D.h"

#include "AnimationComponent.h"
#include "CharacterGameComponent.h"
#include "DeathComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "PlayerStatWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACharacter2D::ACharacter2D()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(RootComponent);

	CharacterGameComponent = CreateDefaultSubobject<UCharacterGameComponent>(TEXT("Character"));

	AnimationComponent = CreateDefaultSubobject<UAnimationComponent>(TEXT("Animation"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("Death"));
}

void ACharacter2D::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacter2D::OnComponentHit);
}

void ACharacter2D::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if(CharacterGameComponent)
	{
		CharacterGameComponent->SetJumping(false);
	}
}

void ACharacter2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(MovementAction)
		{
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered,this,&ACharacter2D::EnhancedMove);
		}
		if(JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter2D::EnhancedJump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter2D::StopJumping);
		}
		if(ClimbAction)
		{
			PlayerEnhancedInputComponent->BindAction(ClimbAction,ETriggerEvent::Triggered,this,&ACharacter2D::EnhancedClimb);
		}
	}
}

float ACharacter2D::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(HealthComponent)
	{
		float UpdatedHealth = HealthComponent->TakeDamage(ActualDamage);

		if(UpdatedHealth == 0.f)
		{
			UpdatedHealth = HealthComponent->GetHealth();
		}

		float MaxHealth = HealthComponent->GetDefaultHealth();
		
		if(CharacterGameComponent)
		{
			CharacterGameComponent->GetPlayerStatWidget()->UpdateHealthBar(UpdatedHealth, MaxHealth);
		}
	}
	
	return ActualDamage;
}

void ACharacter2D::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(CharacterGameComponent)
	{
		CharacterGameComponent->CapsuleComponentHit(HitComponent,OtherActor,OtherComponent,NormalImpulse,Hit);
	}
}

void ACharacter2D::PawnClientRestart()
{
	Super::PawnClientRestart();
	if(APlayerController* LocalPlayer = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext,InputMappingPriority);
		}
	}
}

void ACharacter2D::EnhancedMove(const FInputActionValue& Value)
{
	if(CharacterGameComponent)
	{
		CharacterGameComponent->MoveLeftRight(Value);
	}
}

void ACharacter2D::EnhancedJump(const FInputActionValue& Value)
{
	if(CharacterGameComponent)
	{
		Super::Jump();
		CharacterGameComponent->Jump();
	}
}

void ACharacter2D::EnhancedClimb(const FInputActionValue& Value)
{
	if(CharacterGameComponent)
	{
		CharacterGameComponent->MoveUpDown(Value);
	}
}
