// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "JumperInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AJumperInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
	AJumperInteraction();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, Category="Interaction")
	FVector LaunchVelocity = FVector(0.0f,0.0f,500.f);

	UPROPERTY(EditAnywhere, Category="Interaction")
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, Category="Interaction")
	UPaperSprite* SpriteJumperUp;

	UPROPERTY(EditAnywhere, Category="Interaction")
	UPaperSprite* SpriteJumperDown;

	FTimerHandle TimerHandle;
public:
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetJumper();
};
