#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheelButton.generated.h"

class AWeapon;
class UButton;
class UTextBlock;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	DECLARE_DELEGATE_OneParam(FOnWeaponButtonClicked, AWeapon*);
	FOnWeaponButtonClicked OnWeaponButtonClicked;

	void SetWeaponInfo(AWeapon* WeaponInfo);
	void SetSelected(bool bSelected);

	AWeapon* GetWeapon() const { return Weapon; }

private:
	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY(meta=(BindWidget))
	UButton* WeaponButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponButtonText;

	UFUNCTION()
	void HandleOnButtonClicked();
};