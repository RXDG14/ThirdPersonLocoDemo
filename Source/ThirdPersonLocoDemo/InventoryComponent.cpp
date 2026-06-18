#include "InventoryComponent.h"

#include "Weapons/Weapon.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentWeapon = nullptr;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::PickupWeapon(AWeapon* Weapon)
{
	// Example flow:
	// - find weapon in world
	// - add to WeaponsInInventory
	// - maybe auto equip if nothing is currently equipped
}

void UInventoryComponent::EquipWeapon()
{
	// Optional: equip currently selected/default weapon
	// You can call EquipWeaponFromInventory(CurrentWeapon) here if needed
}

void UInventoryComponent::EquipWeaponFromInventory(AWeapon* Weapon)
{
	if (!Weapon)
	{
		return;
	}

	if (Weapon == CurrentWeapon)
	{
		return;
	}

	CurrentWeapon = Weapon;

	// Put your real equip logic here:
	// - attach weapon to character mesh/socket
	// - hide/disable old weapon
	// - show/enable new weapon
	// - update animation/aim logic if needed
}

void UInventoryComponent::UnEquipWeapon(AWeapon* Weapon)
{
	if (!Weapon)
	{
		return;
	}

	if (Weapon == CurrentWeapon)
	{
		CurrentWeapon = nullptr;
	}

	// Put your real unequip logic here
}

void UInventoryComponent::DropWeapon(AWeapon* Weapon)
{
	if (!Weapon)
	{
		return;
	}

	WeaponsInInventory.Remove(Weapon);

	if (Weapon == CurrentWeapon)
	{
		CurrentWeapon = nullptr;
	}

	// Put your real drop logic here:
	// - detach from character
	// - spawn physics/drop behavior
	// - optionally destroy or re-enable pickup
}

int32 UInventoryComponent::GetNumWeapons() const
{
	return WeaponsInInventory.Num();
}