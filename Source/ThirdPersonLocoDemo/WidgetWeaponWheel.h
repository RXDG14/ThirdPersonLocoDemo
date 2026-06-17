#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheel.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void WeaponWheel_Show();
	void WeaponWheel_Hide();

protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* WeaponList;
	
private:
	UPROPERTY()
	class UWidgetWeaponWheelButton* SelectedWeaponButton;

	UPROPERTY()
	class UInventoryComponent* PlayerInventory;
};
