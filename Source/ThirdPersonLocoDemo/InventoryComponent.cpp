#include "InventoryComponent.h"

#include "Weapon.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::EquipWeapon(APawn* NewOwner)
{
	// pickup or equip weapon from inventory
}

void UInventoryComponent::EquipWeaponFromInventory(class AWeapon* Weapon)
{
	
}

void UInventoryComponent::UnEquipWeapon(AWeapon* Weapon)
{
	// put back in inventory
}

void UInventoryComponent::DropWeapon(AWeapon* Weapon)
{
	// drop weapon and remove from inventory
}

