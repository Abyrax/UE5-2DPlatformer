// abyrax - 2d project


#include "AnimationComponent.h"

#include "Character2D.h"
#include "CharacterGameComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAnimationComponent::UAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAnimationComponent::UpdateControlRotation()
{
	if(CurrentCharacter && CurrentCharacter->GetController())
	{
		if(CurrentCharacter->GetCharacterMovement()->Velocity.X<0.f)
		{
			FRotator Right = FRotator(0.f,180.f,0.f);
			CurrentCharacter->GetController()->SetControlRotation(Right);
		}
		else if(CurrentCharacter->GetCharacterMovement()->Velocity.X>0.f)
		{
			FRotator Left = FRotator(0.f,0.f,0.f);
			CurrentCharacter->GetController()->SetControlRotation(Left);		}
	}
	else
	{
		CharacterState = ECharacterState::Idle;
	}
}

void UAnimationComponent::AnimationStateMachine()
{
	DeathAnimation();
	AttackAnimation();
	JumpAnimation();
	FallAnimation();
	RunAnimation();
	ClimbAnimation();
}

bool UAnimationComponent::RunAnimation()
{
	if(CurrentCharacter && !ClimbAnimation() && !JumpAnimation() && !FallAnimation())
	{
		float Velocity = CurrentCharacter->GetCharacterMovement()->Velocity.Length();
		bool bFalling = CurrentCharacter->GetCharacterMovement()->IsFalling();

		if(Velocity > 0.f && !bFalling && !AttackAnimation())
		{
			CharacterState = ECharacterState::Run;
			return true;
		}
		if(Velocity == 0.f)
		{
			CharacterState = ECharacterState::Idle;
		}
	}
	return false;
}

bool UAnimationComponent::JumpAnimation()
{
	if(CurrentCharacter && !ClimbAnimation())
	{
		if(UCharacterGameComponent* CharacterGameComponent = Owner->FindComponentByClass<UCharacterGameComponent>())
		{
			if(CharacterGameComponent->IsJumping())
			{
				CharacterState = ECharacterState::Jump;
				return true;
			}
		}
	}
	return false;
}

bool UAnimationComponent::AttackAnimation()
{
	return false;
}

bool UAnimationComponent::FallAnimation()
{
	if(CurrentCharacter->GetCharacterMovement()->IsFalling())
	{
		CharacterState = ECharacterState::Fall;
		return true;
	}
	return false;
}

bool UAnimationComponent::DeathAnimation()
{
	return false;
}

bool UAnimationComponent::ClimbAnimation()
{
	if(CurrentCharacter)
	{
		if(UCharacterGameComponent* CharacterGameComponent = CurrentCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			if(CharacterGameComponent->OnLadder())
			{
				const float Velocity = CurrentCharacter->GetCharacterMovement()->Velocity.Length();
				if(Velocity > 0.f)
				{
					CharacterState = ECharacterState::Climb;
				}
				else
				{
					CharacterState = ECharacterState::ClimbIdle;
				}return true;
			}			
		}
	}
	return false;
}

void UAnimationComponent::UpdateAnimation()
{
	if(CurrentCharacter == nullptr)
	{
		return;
	}

	if(!AnimationStructs.IsEmpty())
	{
		for (FAnimationStruct AnimationElement : AnimationStructs)
		{
			if(AnimationElement.AnimationFlipbook && AnimationElement.AnimationState == CharacterState)
			{
				CurrentAnimation = AnimationElement;
				CurrentCharacter->GetSprite()->SetFlipbook(AnimationElement.AnimationFlipbook);
				CurrentCharacter->GetSprite()->SetLooping(AnimationElement.bLoopAnimation);

				if(CurrentAnimation.bLoopAnimation)
				{
					CurrentCharacter->GetSprite()->Play();
				}
				break;
			}
		}
	}
}


// Called when the game starts
void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	CurrentCharacter= Cast<ACharacter2D>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}


// Called every frame
void UAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateControlRotation();
	AnimationStateMachine();
	UpdateAnimation();
}

