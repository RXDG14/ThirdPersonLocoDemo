#include "InventoryComponent.h"
#include "Weapon.h"
#include "ThirdPersonLocoDemo/Enums/TPCWeaponEnums.h"
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
	if (CurrentlyEquippedWeapon)
	{
		AddWeaponToInventory(Weapon);
	}
	else
	{
		AddWeaponToInventory(Weapon);
		AttachWeaponToPlayer(Weapon);	
	}
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
		Weapon->SetOwner(Player);
		Weapon->SetWeaponState(ETPCWeaponState::Equipped);
		Weapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		CurrentlyEquippedWeapon = Weapon;
	}
}

void UInventoryComponent::DetachWeaponFromPlayer()
{
	if (CurrentlyEquippedWeapon)
	{
		CurrentlyEquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentlyEquippedWeapon->SetWeaponState(ETPCWeaponState::UnEquipped);
		CurrentlyEquippedWeapon->SetOwner(nullptr);
		RemoveWeaponFromInventory(CurrentlyEquippedWeapon);
		CurrentlyEquippedWeapon = nullptr;
	}
}

void UInventoryComponent::AddWeaponToInventory(AWeapon* Weapon)
{
	if (!Weapon)
		return;

	for (AWeapon* InventoryWeapon : WeaponsInventory)
	{
		if (!IsValid(InventoryWeapon))
			continue;

		if (InventoryWeapon->GetClass() == Weapon->GetClass())
		{
			AddWeaponAsAmmo(Weapon);
			return;
		}
	}

	WeaponsInventory.Add(Weapon);
}

void UInventoryComponent::RemoveWeaponFromInventory(AWeapon* Weapon)
{
	WeaponsInventory.RemoveSingle(Weapon);
}

void UInventoryComponent::AddWeaponAsAmmo(AWeapon* Weapon)
{
	// Increase the ammo of this weapon which we already have
	// then we destroy this weapon which we don't need physical version of
	Weapon->K2_DestroyActor();
	UE_LOG(LogTemp,Warning,TEXT ("Destroyed"));
}
