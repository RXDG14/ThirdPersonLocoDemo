#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheel.generated.h"

class UWidgetWeaponWheelButton;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void WeaponWheel_Show();
	void WeaponWheel_Hide();
	
	UPROPERTY(EditDefaultsOnly, Category="WeaponWheel")
	TSubclassOf<UWidgetWeaponWheelButton> WeaponButtonClass;

	void SetInventoryComponent(class UInventoryComponent* InInventoryComponent);
	
private:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* WeaponsList;

	UPROPERTY(meta=(BindWidget))
	class UButton* DropAllWeaponsButton;

	UPROPERTY()
	TObjectPtr<UWidgetWeaponWheelButton> SelectedWeaponButton;
	
	UPROPERTY()
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UFUNCTION()
	void OnDropAllWeaponsButtonClicked();

	UFUNCTION()
	void OnWeaponButtonHovered(class UWidgetWeaponWheelButton* WeaponButton);

	UFUNCTION()
	void OnWeaponButtonUnHovered(class UWidgetWeaponWheelButton* WeaponButton);
	
	void RefreshWeaponsList();
	void SetSelectedWeapon();
};