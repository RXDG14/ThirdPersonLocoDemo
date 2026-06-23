#include "WidgetWeaponWheelButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWidgetWeaponWheelButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeaponButton)
	{
		WeaponButton->OnClicked.AddDynamic(this, &UWidgetWeaponWheelButton::OnButtonClicked);
	}
}

void UWidgetWeaponWheelButton::SetWeaponButtonText(const FText& NewText)
{
	if (WeaponButtonText)
	{
		WeaponButtonText->SetText(NewText);
	}
}

void UWidgetWeaponWheelButton::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Button Clicked"));
}
