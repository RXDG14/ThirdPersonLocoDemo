#include "WidgetWeaponWheel.h"
#include "WidgetWeaponWheelButton.h"
#include "Components/VerticalBox.h"
#include "ThirdPersonLocoDemo/Weapons/InventoryComponent.h"
#include "ThirdPersonLocoDemo/Weapons/Weapon.h"
#include "ThirdPersonLocoDemo/Weapons/WeaponData.h"

void UWidgetWeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetWeaponWheel::WeaponWheel_Show()
{
	SetVisibility(ESlateVisibility::Visible);

	RefreshWeaponsList();
}

void UWidgetWeaponWheel::WeaponWheel_Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetWeaponWheel::SetInventoryComponent(class UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;
}

void UWidgetWeaponWheel::RefreshWeaponsList()
{
	if (!WeaponsList || !WeaponButtonClass || !InventoryComponent)
		return;

	WeaponsList->ClearChildren();

	const TArray<AWeapon*>& Weapons = InventoryComponent->GetWeaponsInventory();

	for (AWeapon* Weapon : Weapons)
	{
		if (!IsValid(Weapon))
			continue;

		UWidgetWeaponWheelButton* WeaponButton = CreateWidget<UWidgetWeaponWheelButton>(GetWorld(), WeaponButtonClass);
		if (!WeaponButton)
			continue;

		WeaponButton->SetWeaponButtonText(Weapon->GetWeaponData()->WeaponName);
		WeaponsList->AddChild(WeaponButton);
	}
}
