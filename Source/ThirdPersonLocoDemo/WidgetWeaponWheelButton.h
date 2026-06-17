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

	DECLARE_DELEGATE_OneParam(FOnWeaponButtonClicked, class AWeapon*);
	FOnWeaponButtonClicked OnWeaponButtonClicked;
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* WeaponButton;

private:
	UPROPERTY()
	class AWeapon* Weapon;

	UFUNCTION()
	void HandleOnButtonClicked();
};
