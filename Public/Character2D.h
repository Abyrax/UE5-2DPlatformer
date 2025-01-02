// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Character2D.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECT2D_API ACharacter2D : public APaperCharacter
{
	GENERATED_BODY()
	ACharacter2D();
public:
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category="Actor Component")
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
private:
	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class UCharacterGameComponent* CharacterGameComponent;
	
	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class UAnimationComponent* AnimationComponent;

	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class UDeathComponent* DeathComponent;

	UPROPERTY(VisibleAnywhere, Category= "Actor Component")
	class UHealthComponent* HealthComponent;
	
protected:

	virtual void PawnClientRestart() override;
	
#pragma region INPUT

	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* ClimbAction;

	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	int32 InputMappingPriority = 0;

public:
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedJump(const FInputActionValue& Value);
	void EnhancedClimb(const FInputActionValue& Value);
#pragma endregion
};
