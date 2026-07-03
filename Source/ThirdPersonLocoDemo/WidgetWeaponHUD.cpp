#include "WidgetWeaponHUD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidgetWeaponHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetWeaponHUD::SetCurrentAmmoInClip(int32 Amount)
{
	CurrentAmmoInClipText->SetText(FText::AsNumber(Amount));
}

void UWidgetWeaponHUD::SetAmmoClipSize(int32 Amount)
{
	AmmoClipSizeText->SetText(FText::AsNumber(Amount));
}

void UWidgetWeaponHUD::SetTotalRemainingSpareAmmo(int32 Amount)
{
	TotalRemainingSpareAmmoText->SetText(FText::AsNumber(Amount));
}

void UWidgetWeaponHUD::SetWeaponImage(UTexture2D* Texture)
{
	if (WeaponImage && Texture)
	{
		WeaponImage->SetBrushFromTexture(Texture);
	}
}

void UWidgetWeaponHUD::SetWeaponHUDVisiblity(bool value)
{
	if (value)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}
