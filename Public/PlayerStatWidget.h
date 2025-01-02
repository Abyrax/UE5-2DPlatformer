// abyrax - 2d project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	void InitHealthWidget();
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget), Category="Widget")
	class UProgressBar* PlayerHealthBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget), Category="Widget")
	class UTextBlock* numCollectibles;

	UFUNCTION(BlueprintCallable, Category="Widget")
	void UpdateHealthBar(float Health, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category="Widget")
	void UpdateCollectible(float collectible);
	
private:
	FTimerHandle TimerHandle;
};
