// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()
public:
	AEnemyBase();
	void ToggleFacingDirection();
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;


	UPROPERTY(VisibleAnywhere, Category="EnemyActor")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category="EnemyActor")
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category="EnemyActor")
	class UDeathComponent* DeathComponent;

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	class ACharacter2D* PlayerCharacter;

#pragma region MOVEMENT
	void Move();
	void FollowCharacter();
#pragma endregion

	virtual void OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal){}
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){}
	virtual void OnSphereOverlapped(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){}
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex){}

protected:

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	bool bEnemyMoveRight = false;

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	bool bFollowing = false;

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	FVector EWorldDirection = FVector(1.0f,0.0f,0.0f);

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	float MaxDistanceBetweenCharacter = 40.f;

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	bool bCanTakeDamage = false;

	UPROPERTY(EditAnywhere, Category="EnemyActor")
	float DefaultDamageAmount = 10.f;

public:
	float GetDamageAmount() const
	{
		return DefaultDamageAmount;
	}

	bool CanTakeDamage() const
	{
		return bCanTakeDamage;
	}
};
