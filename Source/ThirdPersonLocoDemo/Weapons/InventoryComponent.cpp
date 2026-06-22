#include "InventoryComponent.h"
#include "Weapon.h"
#include "ThirdPersonLocoDemo/Player/TPCharacter.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::PickupWeapon(class AWeapon* Weapon)
{
	AddWeaponToInventory(Weapon);
	AttachWeaponToPlayer(Weapon);
}

void UInventoryComponent::DropWeapon()
{
	DetachWeaponFromPlayer();
}

void UInventoryComponent::AttachWeaponToPlayer(AWeapon* Weapon)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (Player && Player->GetMesh())
	{
		Weapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		CurrentlyEquippedWeapon = Weapon;
	}
}

void UInventoryComponent::DetachWeaponFromPlayer()
{
	if (CurrentlyEquippedWeapon)
	{
		CurrentlyEquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		RemoveWeaponFromInventory(CurrentlyEquippedWeapon);
		CurrentlyEquippedWeapon = nullptr;
	}
}

void UInventoryComponent::AddWeaponToInventory(AWeapon* Weapon)
{
	WeaponsInventory.Add(Weapon);
}

void UInventoryComponent::RemoveWeaponFromInventory(AWeapon* Weapon)
{
	WeaponsInventory.RemoveSingle(Weapon);
}
