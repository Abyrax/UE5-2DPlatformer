// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2D_API UDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeathComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsDead = false;

public:
	
	UFUNCTION(BlueprintPure, Category="CharacterStat")
	bool IsDead() const
	{
		return bIsDead;
	}
	
	UFUNCTION(BlueprintCallable, Category="CharacterStat")
	void SetIsDead(bool bNewIsDead)
	{
		this->bIsDead = bNewIsDead;
	}
	
	UFUNCTION(BlueprintCallable, Category="CharacterStat")
	void OnDeath();
};
