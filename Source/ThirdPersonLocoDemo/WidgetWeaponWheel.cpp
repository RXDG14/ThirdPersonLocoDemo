#include "WidgetWeaponWheel.h"

void UWidgetWeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetWeaponWheel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWidgetWeaponWheel::WeaponWheel_Show()
{
}

void UWidgetWeaponWheel::WeaponWheel_Hide()
{
}

int32 UWidgetWeaponWheel::GetSelectedSlot() const
{
	return -1;
}
