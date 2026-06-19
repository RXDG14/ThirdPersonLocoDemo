#include "WidgetWeaponWheel.h"
#include "../Weapons/InventoryComponent.h"
#include "../Weapons/Weapon.h"
#include "WidgetWeaponWheelButton.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UWidgetWeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		PlayerInventory = Pawn->FindComponentByClass<UInventoryComponent>();
	}
}

void UWidgetWeaponWheel::WeaponWheel_Show()
{
	if (!PlayerInventory)
		return;

	SelectedWeapon = PlayerInventory->GetCurrentWeapon();

	BuildWeaponList();
	RefreshSelection();

	SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void UWidgetWeaponWheel::WeaponWheel_Hide()
{
	if (PlayerInventory && SelectedWeapon)
	{
		PlayerInventory->EquipWeaponFromInventory(SelectedWeapon);
	}

	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void UWidgetWeaponWheel::BuildWeaponList()
{
	if (!WeaponList || !PlayerInventory || !WeaponButtonClass)
		return;

	WeaponList->ClearChildren();
	WeaponButtons.Empty();

	const int32 NumWeapons = PlayerInventory->GetNumWeapons();

	for (int32 i = 0; i < NumWeapons; i++)
	{
		AWeapon* Weapon = PlayerInventory->WeaponsInInventory[i];
		if (!Weapon)
			continue;

		UWidgetWeaponWheelButton* WeaponButton = CreateWidget<UWidgetWeaponWheelButton>(GetOwningPlayer(), WeaponButtonClass);
		if (!WeaponButton)
			continue;

		WeaponButton->SetWeaponInfo(Weapon);
		WeaponButton->OnWeaponButtonClicked.BindUObject(this, &UWidgetWeaponWheel::SelectWeapon);

		WeaponButtons.Add(WeaponButton);
		WeaponList->AddChild(WeaponButton);
	}
}

void UWidgetWeaponWheel::SelectWeapon(AWeapon* Weapon)
{
	SelectedWeapon = Weapon;
	RefreshSelection();
}

void UWidgetWeaponWheel::RefreshSelection()
{
	for (UWidgetWeaponWheelButton* Button : WeaponButtons)
	{
		if (Button)
		{
			Button->SetSelected(Button->GetWeapon() == SelectedWeapon);
		}
	}
}