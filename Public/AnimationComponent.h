// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"

UENUM(BlueprintType)
enum ECharacterState
{
	Idle,
	Run,
	Jump,
	Attack,
	Climb,
	ClimbIdle,
	Fall,
	Dead
};

USTRUCT(BlueprintType)
struct FAnimationStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct")
	TEnumAsByte<ECharacterState> AnimationState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct")
	UPaperFlipbook* AnimationFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct")
	bool bLoopAnimation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2D_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationComponent();
	void UpdateControlRotation();
	void AnimationStateMachine();

	bool RunAnimation();
	bool JumpAnimation();
	bool AttackAnimation();
	bool FallAnimation();
	bool DeathAnimation();

	bool ClimbAnimation();

	void UpdateAnimation();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(VisibleAnywhere, Category="Player")
	class ACharacter2D* CurrentCharacter;

	UPROPERTY(VisibleAnywhere, Category="Player")
	AActor* Owner;

	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, Category="Animation")
	TArray<FAnimationStruct> AnimationStructs;

	FAnimationStruct CurrentAnimation; 

};
