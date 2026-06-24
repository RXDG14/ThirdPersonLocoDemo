#include "WidgetWeaponWheel.h"
#include "WidgetWeaponWheelButton.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "ThirdPersonLocoDemo/Weapons/InventoryComponent.h"
#include "ThirdPersonLocoDemo/Weapons/Weapon.h"
#include "ThirdPersonLocoDemo/Weapons/WeaponData.h"

void UWidgetWeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();

	if (DropAllWeaponsButton)
	{
		DropAllWeaponsButton->OnClicked.AddDynamic(this, &UWidgetWeaponWheel::OnDropAllWeaponsButtonClicked);
	}
}

void UWidgetWeaponWheel::WeaponWheel_Show()
{
	SetVisibility(ESlateVisibility::Visible);
	RefreshWeaponsList();
}

void UWidgetWeaponWheel::WeaponWheel_Hide()
{
	SetSelectedWeapon();
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
	SelectedWeaponButton = nullptr;
	
	const TArray<AWeapon*>& Weapons = InventoryComponent->GetWeaponsInventory();
	for (AWeapon* Weapon : Weapons)
	{
		if (!IsValid(Weapon))
			continue;

		UWidgetWeaponWheelButton* WeaponButton = CreateWidget<UWidgetWeaponWheelButton>(GetWorld(), WeaponButtonClass);
		if (!WeaponButton)
			continue;

		WeaponButton->SetWeaponButtonText(Weapon->GetWeaponData()->WeaponName);
		WeaponButton->SetWeaponButtonWeapon(Weapon);

		WeaponButton->OnWeaponButtonHovered.AddUObject(this, &UWidgetWeaponWheel::OnWeaponButtonHovered);
		WeaponButton->OnWeaponButtonUnHovered.AddUObject(this, &UWidgetWeaponWheel::OnWeaponButtonUnHovered);
		
		WeaponsList->AddChild(WeaponButton);
	}
}

void UWidgetWeaponWheel::SetSelectedWeapon()
{
	if (!SelectedWeaponButton || !InventoryComponent)
		return;

	AWeapon* Weapon = SelectedWeaponButton->GetWeaponButtonWeapon();
	if (!Weapon)
		return;

	InventoryComponent->EquipWeaponFromInventory(Weapon);
}

void UWidgetWeaponWheel::OnDropAllWeaponsButtonClicked()
{
	if (InventoryComponent)
	{
		InventoryComponent->DropAllWeapons();
	}
}

void UWidgetWeaponWheel::OnWeaponButtonHovered(UWidgetWeaponWheelButton* WeaponButton)
{
	if (!WeaponButton)
		return;

	if (SelectedWeaponButton && SelectedWeaponButton != WeaponButton)
	{
		SelectedWeaponButton->SetWeaponButtonSelection(false);
	}

	SelectedWeaponButton = WeaponButton;
	SelectedWeaponButton->SetWeaponButtonSelection(true);
}

void UWidgetWeaponWheel::OnWeaponButtonUnHovered(class UWidgetWeaponWheelButton* WeaponButton)
{
	if (!WeaponButton)
		return;

	if (WeaponButton == SelectedWeaponButton)
	{
		WeaponButton->SetWeaponButtonSelection(false);
		SelectedWeaponButton = nullptr;
	}
}
