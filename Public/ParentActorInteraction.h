// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "Character2D.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "ParentActorInteraction.generated.h"

UCLASS()
class PROJECT2D_API AParentActorInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentActorInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Interaction")
	class UPaperSpriteComponent* PaperSprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Interaction")
	ACharacter2D* PlayerCharacter;
};
