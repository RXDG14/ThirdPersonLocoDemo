#include "WidgetWeaponWheelButton.h"
#include "Weapons/Weapon.h"
#include "WeaponData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWidgetWeaponWheelButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeaponButton)
	{
		WeaponButton->OnClicked.RemoveAll(this);
		WeaponButton->OnClicked.AddDynamic(this, &UWidgetWeaponWheelButton::HandleOnButtonClicked);
	}
}

void UWidgetWeaponWheelButton::HandleOnButtonClicked()
{
	if (Weapon)
	{
		OnWeaponButtonClicked.ExecuteIfBound(Weapon);
	}
}

void UWidgetWeaponWheelButton::SetWeaponInfo(AWeapon* WeaponInfo)
{
	Weapon = WeaponInfo;

	if (!WeaponButtonText || !Weapon)
	{
		return;
	}

	if (UWeaponData* WeaponData = Weapon->GetWeaponData())
	{
		WeaponButtonText->SetText(WeaponData->WeaponName);
	}
}

void UWidgetWeaponWheelButton::SetSelected(bool bSelected)
{
	if (!WeaponButtonText)
	{
		return;
	}

	if (bSelected)
	{
		if (UWeaponData* WeaponData = Weapon->GetWeaponData())
		{
			WeaponButtonText->SetText(FText::FromString(TEXT("✓ ") + WeaponData->WeaponName.ToString()));
		}
	}
	else
	{
		if (UWeaponData* WeaponData = Weapon->GetWeaponData())
		{
			WeaponButtonText->SetText(WeaponData->WeaponName);
		}
	}
}