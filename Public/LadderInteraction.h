// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LadderInteraction.generated.h"

UCLASS()
class PROJECT2D_API ALadderInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadderInteraction();
private:
	UPROPERTY(VisibleAnywhere,Category="Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere,Category="Interaction")
	class ACharacter2D* PlayerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
