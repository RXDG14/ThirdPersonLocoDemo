#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheelButton.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetWeaponButtonText(const FText& NewText);
	
private:
	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY(meta=(BindWidget))
	class UButton* WeaponButton;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* WeaponButtonText;
};