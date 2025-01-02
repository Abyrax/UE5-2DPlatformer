// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySimple.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemySimple : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AEnemySimple();

private:
	bool bAlreadyHit = false;

	UPROPERTY(EditAnywhere,Category ="Enemy")
	bool bCanFollow = false;

	virtual void BeginPlay() override;;

	UFUNCTION(BlueprintCallable,Category ="Enemy")
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable,Category ="Enemy")
	virtual void OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal) override;

	UFUNCTION(BlueprintCallable,Category ="Enemy")
	virtual void OnSphereOverlapped(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintCallable,Category ="Enemy")
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex) override;

	void ResetHit();

	FTimerHandle TimerHandle;
public:
	virtual void Tick(float DeltaSeconds) override;
};
