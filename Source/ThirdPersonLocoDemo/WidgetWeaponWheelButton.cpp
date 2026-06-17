#include "WidgetWeaponWheelButton.h"
#include "Components/Button.h"

void UWidgetWeaponWheelButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeaponButton)
	{
		WeaponButton->OnClicked.AddDynamic(this,&UWidgetWeaponWheelButton::HandleOnButtonClicked);
	}
}

void UWidgetWeaponWheelButton::HandleOnButtonClicked()
{
	
}
