// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CharacterGameComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2D_API UCharacterGameComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterGameComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		void MoveLeftRight(const FInputActionValue& Value);

		void MoveUpDown(const FInputActionValue& Value);

		void Jump();

		float IncrementCollectible();

		void CapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
private:
	UPROPERTY(VisibleAnywhere, Category="Player")
	class ACharacter2D* CurrentCharacter;
	
	UPROPERTY(VisibleAnywhere, Category="Player")
	AActor* Owner;

	bool bJumping;

	bool bOnLadder;

	UPROPERTY(EditAnywhere, Category="Widget")
	float collectible;

	UPROPERTY(EditAnywhere, Category="Widget")
	float DefaultDamageAmount;

public:
	float GetDefaultDamageAmount1() const
	{
		return DefaultDamageAmount;
	}

private:
	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<class UPlayerStatWidget> PlayerStatWidgetClass;

	UPROPERTY(VisibleAnywhere, Category="Widget")
	class UPlayerStatWidget* PlayerStatWidget;

	UPROPERTY(VisibleAnywhere, Category="Widget")
	class AEnemyBase* EnemyBase;

public:
	
	UPlayerStatWidget* GetPlayerStatWidget() const
	{
		return PlayerStatWidget;
	}

	bool OnLadder() const
	{
		return bOnLadder;
	}

	void SetOnLadder(bool bNewOnLadder)
	{
		this->bOnLadder = bNewOnLadder;
	}

	bool IsJumping() const
	{
		return bJumping;
	}

	void SetJumping(bool bNewJumping)
	{
		this->bJumping = bNewJumping;
	}
};
