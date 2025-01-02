// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "SpikeInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API ASpikeInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
public:
	ASpikeInteraction();
	
	void ChangeSpikeStatus();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void ActivateSpike();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void DeactivateSpike();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Interaction")
	bool bSpikeUp = false;

	UPROPERTY(EditAnywhere,Category="Interaction")
	bool bLooping = true;

	UPROPERTY(EditAnywhere,Category="Interaction")
	float DamageAmount = 10.f;

	UPROPERTY(EditAnywhere,Category="Interaction")
	float Duration = 4.f;
	
	UPROPERTY(EditAnywhere,Category="Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere,Category="Interaction")
	class UPaperSprite* SpriteSpikeUp;

	UPROPERTY(EditAnywhere,Category="Interaction")
	UPaperSprite* SpriteSpikeDown;
	
	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
