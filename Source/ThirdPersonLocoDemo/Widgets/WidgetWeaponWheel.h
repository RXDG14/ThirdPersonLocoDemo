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

	UPROPERTY()
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	void RefreshWeaponsList();
};