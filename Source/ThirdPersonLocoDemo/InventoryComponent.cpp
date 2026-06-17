#include "InventoryComponent.h"

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

void UInventoryComponent::EquipWeapon(APawn* NewOwner, int32 WeaponSlot)
{
}

void UInventoryComponent::UnEquipWeapon(int32 WeaponSlot)
{
}

void UInventoryComponent::DropWeapon(int32 WeaponSlot)
{
}

