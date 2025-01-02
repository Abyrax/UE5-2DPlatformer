// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "CollectibleInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API ACollectibleInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
	ACollectibleInteraction();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	class UBoxComponent* BoxComponent;
public:
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
