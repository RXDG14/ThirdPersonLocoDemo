#include "InventoryComponent.h"
#include "../Weapons/Weapon.h"

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
	// add to inventory
	// attach to player
}

void UInventoryComponent::EquipWeaponFromInventory(AWeapon* Weapon)
{
	if (!Weapon)
		return;

	if (Weapon == CurrentWeapon)
		return;

	UnEquipWeapon(CurrentWeapon); // add back to inventory
	
	CurrentWeapon = Weapon;

	// attach to player
}

void UInventoryComponent::UnEquipWeapon(AWeapon* Weapon)
{
	if (!Weapon)
		return;

	if (Weapon == CurrentWeapon)
	{
		CurrentWeapon = nullptr;
	}

	// detach weapon from player
}

void UInventoryComponent::DropWeapon(AWeapon* Weapon)
{
	if (!Weapon)
		return;

	WeaponsInInventory.Remove(Weapon);

	if (Weapon == CurrentWeapon)
	{
		CurrentWeapon = nullptr;
	}

	// detach from player
	// remove from inventory
}

int32 UInventoryComponent::GetNumWeapons() const
{
	return WeaponsInInventory.Num();
}