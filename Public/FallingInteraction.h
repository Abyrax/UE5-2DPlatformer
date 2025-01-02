// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FallingInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AFallingInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
	AFallingInteraction();
private:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Interaction")
	TSubclassOf<AFallingInteraction> FallingInteractionClass;

	UPROPERTY(VisibleAnywhere,Category="Interaction")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly,Category="Interaction")
	float DropDelay = 2.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="Interaction")
	float RespawnDelay = 2.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="Interaction")
	bool bDestroy = true;
	UPROPERTY(EditDefaultsOnly,Category="Interaction")
	bool bRespawn = true;

	//UPROPERTY(EditDefaultsOnly,Category="Interaction")
	FVector StartLocation;

	//UPROPERTY(EditDefaultsOnly,Category="Interaction")
	FTimerHandle TimerHandle;

	bool bAlreadyOnFall;
public:
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void OnFall();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void OnReset();
};
