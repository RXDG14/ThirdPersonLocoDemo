#include "WidgetWeaponWheelButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWidgetWeaponWheelButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeaponButton)
	{
		WeaponButton->OnHovered.AddDynamic(this, &UWidgetWeaponWheelButton::OnButtonHovered);
		WeaponButton->OnUnhovered.AddDynamic(this, &UWidgetWeaponWheelButton::OnButtonUnHovered);
	}
}

void UWidgetWeaponWheelButton::SetWeaponButtonText(const FText& NewText)
{
	WeaponButtonOriginalText = NewText;
	if (WeaponButtonText)
	{
		WeaponButtonText->SetText(NewText);
	}
}

void UWidgetWeaponWheelButton::SetWeaponButtonWeapon(AWeapon* InWeapon)
{
	if (InWeapon)
	{
		Weapon = InWeapon;
	}
}

void UWidgetWeaponWheelButton::SetWeaponButtonSelection(bool bSetAsSelected)
{
	if (!WeaponButtonText)
		return;

	if (bSetAsSelected)
	{
		SetWeaponButtonText(FText::Format(FText::FromString(TEXT("--> {0}")),WeaponButtonText->GetText()));
		bIsSelected = true;	
	}
	else
	{
		SetWeaponButtonText(WeaponButtonOriginalText);
		bIsSelected = false;
	}
}

bool UWidgetWeaponWheelButton::GetIsSelected()
{
	return bIsSelected;
}

AWeapon* UWidgetWeaponWheelButton::GetWeaponButtonWeapon()
{
	return Weapon;
}

void UWidgetWeaponWheelButton::OnButtonHovered()
{
	OnWeaponButtonHovered.Broadcast(this);
}

void UWidgetWeaponWheelButton::OnButtonUnHovered()
{
	OnWeaponButtonUnHovered.Broadcast(this);
}
