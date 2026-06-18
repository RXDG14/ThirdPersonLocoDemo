#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheel.generated.h"

class AWeapon;
class UInventoryComponent;
class UVerticalBox;
class UWidgetWeaponWheelButton;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void WeaponWheel_Show();
	void WeaponWheel_Hide();
	void BuildWeaponList();

protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* WeaponList;

	UPROPERTY(EditDefaultsOnly, Category="Weapons")
	TSubclassOf<UWidgetWeaponWheelButton> WeaponButtonClass;

private:
	UPROPERTY()
	AWeapon* SelectedWeapon;

	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	TArray<UWidgetWeaponWheelButton*> WeaponButtons;

	void SelectWeapon(AWeapon* Weapon);
	void RefreshSelection();
};