#include "WidgetWeaponWheel.h"

#include "InventoryComponent.h"
#include "WidgetWeaponWheelButton.h"
#include "Kismet/GameplayStatics.h"

void UWidgetWeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		PlayerInventory = Pawn->FindComponentByClass<UInventoryComponent>();
		UE_LOG(LogTemp, Warning, TEXT("Player Inventory"));
	}
}

void UWidgetWeaponWheel::WeaponWheel_Show()
{
	SetVisibility(ESlateVisibility::Visible);
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void UWidgetWeaponWheel::WeaponWheel_Hide()
{
	//PlayerInventory->EquipWeaponFromInventory(SelectedWeaponButton)
	
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}
