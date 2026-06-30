#include "InventoryComponent.h"
#include "Weapon.h"
#include "WeaponData.h"
#include "ThirdPersonLocoDemo/Enums/TPCPlayerEnums.h"
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

void UInventoryComponent::PickupWeapon(AWeapon* Weapon)
{
	if (!IsValid(Weapon))
		return;

	if (HasWeaponEquipped())
	{
		// add to inventory
		AddWeaponToInventory(Weapon,true);
	}
	else
	{
		// Equip weapon
		EquipWeapon(Weapon);
	}
}

void UInventoryComponent::DropCurrentlyEquippedWeapon()
{
	if (!HasWeaponEquipped())
		return;

	UnEquipWeapon(CurrentlyEquippedWeapon, false);
}

void UInventoryComponent::HolsterCurrentlyEquippedWeapon()
{
	if (!HasWeaponEquipped())
		return;

	HolsterWeapon(CurrentlyEquippedWeapon);
}

void UInventoryComponent::DropAllWeapons()
{
	TArray<AWeapon*> WeaponsToDrop = WeaponsInventory;
	
	if (IsValid(CurrentlyEquippedWeapon))
	{
		WeaponsToDrop.AddUnique(CurrentlyEquippedWeapon);
	}

	for (AWeapon* InventoryWeapon : WeaponsToDrop)
	{
		if (!IsValid(InventoryWeapon))
			continue;

		UnEquipWeapon(InventoryWeapon, false);
	}
}

void UInventoryComponent::EquipWeaponFromInventory(AWeapon* Weapon)
{
	if (HasWeaponEquipped())
	{
		if (CurrentlyEquippedWeapon == Weapon)
			return;
		
		HolsterWeapon(CurrentlyEquippedWeapon);
		EquipWeapon(Weapon);
	}
	else
	{
		EquipWeapon(Weapon);
	}
}

void UInventoryComponent::AddWeaponToInventory(AWeapon* NewWeapon, bool bShouldHolster)
{
	if (!IsValid(NewWeapon) || !IsValid(NewWeapon->GetWeaponData()))
		return;

	UWeaponData* NewWeaponData = NewWeapon->GetWeaponData();

	for (AWeapon* InventoryWeapon : WeaponsInventory) //  check if weapon already exists in inv
	{
		if (!IsValid(InventoryWeapon) || !IsValid(InventoryWeapon->GetWeaponData()))
			continue;

		if (InventoryWeapon == NewWeapon)
			continue;

		UWeaponData* InventoryWeaponData = InventoryWeapon->GetWeaponData();

		if (InventoryWeaponData->WeaponID == NewWeaponData->WeaponID)
		{
			AddWeaponToInventoryAsAmmo(NewWeapon); // add as ammo if already exists
			return;
		}
	}

	WeaponsInventory.AddUnique(NewWeapon);
	if (bShouldHolster)
	{
		HolsterWeapon(NewWeapon);
	}
	UE_LOG(LogTemp, Warning, TEXT("Added weapon to inventory"));
}

void UInventoryComponent::RemoveWeaponFromInventory(AWeapon* Weapon)
{
	WeaponsInventory.RemoveSingle(Weapon);
}

void UInventoryComponent::AddWeaponToInventoryAsAmmo(AWeapon* NewWeapon)
{
	// add weapon ammo then destroy physical weapon in world
	NewWeapon->K2_DestroyActor();
}

void UInventoryComponent::EquipWeapon(AWeapon* Weapon)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;

	AddWeaponToInventory(Weapon, false);
	Weapon->SetOwner(Player);
	Weapon->SetWeaponState(ETPCWeaponState::Equipped);
	if (Weapon->GetWeaponData())
	{
		Weapon->AttachToComponent(Player->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,Weapon->GetWeaponData()->WeaponEquippedSocketName);
		SetPlayerAnimationState(Weapon->GetWeaponData()->WeaponType);
	}
	CurrentlyEquippedWeapon = Weapon;
}

void UInventoryComponent::UnEquipWeapon(AWeapon* Weapon, bool bShouldHolster)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;

	if (bShouldHolster)
	{
		HolsterWeapon(Weapon);
	}
	else
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->SetWeaponState(ETPCWeaponState::UnEquipped);
		Weapon->SetOwner(nullptr);
		RemoveWeaponFromInventory(Weapon);
		CurrentlyEquippedWeapon = nullptr;
		SetPlayerAnimationState(EWeaponType::None);
	}
}

void UInventoryComponent::HolsterWeapon(AWeapon* Weapon)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;
	
	if (HasWeaponEquipped())
	{
		if (CurrentlyEquippedWeapon == Weapon)
		{
			CurrentlyEquippedWeapon = nullptr;
		}
	}
	
	Weapon->SetOwner(Player);
	Weapon->SetWeaponState(ETPCWeaponState::Holstered);
	if (Weapon->GetWeaponData())
	{
		Weapon->AttachToComponent(Player->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,Weapon->GetWeaponData()->WeaponHolsterSocketName);
	}
}

void UInventoryComponent::SetPlayerAnimationState(EWeaponType WeaponType)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;
	
	switch (WeaponType)
	{
	case EWeaponType::None:
		Player->SetTPCAnimationState(ETPCAnimationState::Unarmed);
		break;
	case EWeaponType::Pistol:
		Player->SetTPCAnimationState(ETPCAnimationState::Pistol);
		break;
	case EWeaponType::Rifle:
		Player->SetTPCAnimationState(ETPCAnimationState::Rifle);
		break;
	default:
		break;
	}
}

bool UInventoryComponent::HasWeaponEquipped() const
{
	return CurrentlyEquippedWeapon != nullptr;
}

EWeaponType UInventoryComponent::GetCurrentlyEquippedWeaponType()
{
	if (HasWeaponEquipped() && CurrentlyEquippedWeapon)
	{
		auto* CurrentlyEquippedWeaponData = CurrentlyEquippedWeapon->GetWeaponData();
		if (!CurrentlyEquippedWeaponData)
			return EWeaponType::None;

		return CurrentlyEquippedWeaponData->WeaponType;
	}

	return EWeaponType::None;
}

void UInventoryComponent::ChangeWeaponSocket(FName NewWeaponSocketName)
{
	if (!HasWeaponEquipped() && CurrentlyEquippedWeapon)
		return;

	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;

	if (CurrentlyEquippedWeapon->GetWeaponData())
	{
		CurrentlyEquippedWeapon->AttachToComponent(Player->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,NewWeaponSocketName);
	}
}
