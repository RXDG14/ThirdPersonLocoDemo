#include "InventoryComponent.h"
#include "Weapon.h"
#include "WeaponData.h"
#include "WeaponRanged.h"
#include "ThirdPersonLocoDemo/WidgetWeaponHUD.h"
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
	//UpdateWeaponUI(true);
}

void UInventoryComponent::DropCurrentlyEquippedWeapon()
{
	if (!HasWeaponEquipped())
		return;

	UnEquipWeapon(CurrentlyEquippedWeapon, false);
	UpdateWeaponUI(false);
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

bool UInventoryComponent::AddWeaponToInventory(AWeapon* NewWeapon, bool bShouldHolster)
{
	if (!IsValid(NewWeapon) || !IsValid(NewWeapon->GetWeaponData()))
	{
		return false;
	}

	if (IsWeaponAlreadyInInventory(NewWeapon))
	{
		AddWeaponToInventoryAsAmmo(NewWeapon);
		return false;
	}

	WeaponsInventory.AddUnique(NewWeapon);

	if (bShouldHolster)
	{
		HolsterWeapon(NewWeapon);
	}

	NewWeapon->OnWeaponStatsUpdated.BindUObject(this, &UInventoryComponent::UpdateWeaponStats);
	NewWeapon->TellPlayerToReload.BindUObject(this, &UInventoryComponent::SignalPlayerToReload);

	UE_LOG(LogTemp, Warning, TEXT("Added weapon to inventory"));

	return true;
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
	{
		return;
	}

	// Weapon wasn't added (likely converted to ammo).
	if (!AddWeaponToInventory(Weapon, false))
	{
		return;
	}

	Weapon->SetOwner(Player);
	Weapon->SetWeaponState(ETPCWeaponState::Equipped);

	if (Weapon->GetWeaponData())
	{
		Weapon->AttachToComponent(
			Player->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			Weapon->GetWeaponData()->WeaponEquippedSocketName);

		SetPlayerAnimationState(Weapon->GetWeaponData()->WeaponType);
	}

	CurrentlyEquippedWeapon = Weapon;
	UpdateWeaponUI(true);
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
	UpdateWeaponUI(false);
}

void UInventoryComponent::HolsterWeapon(AWeapon* Weapon)
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;

	const bool bWasEquipped = (CurrentlyEquippedWeapon == Weapon);

	if (bWasEquipped)
	{
		CurrentlyEquippedWeapon = nullptr;
	}

	Weapon->SetOwner(Player);
	Weapon->SetWeaponState(ETPCWeaponState::Holstered);

	if (Weapon->GetWeaponData())
	{
		Weapon->AttachToComponent(
			Player->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			Weapon->GetWeaponData()->WeaponHolsterSocketName);
	}

	if (bWasEquipped)
	{
		UpdateWeaponUI(false);
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

void UInventoryComponent::UpdateWeaponUI(bool bVisibility)
{
	if (HasWeaponEquipped() && CurrentlyEquippedWeapon)
	{
		if (GetCurrentlyEquippedWeaponCategory() == EWeaponCategory::Ranged)
		{
			auto* Weapon = Cast<AWeaponRanged>(CurrentlyEquippedWeapon);
			UpdateWeaponStats(Weapon->GetCurrentAmmo(),Weapon->GetAmmoClipSize(),Weapon->GetSpareAmmo());
			
		}
	}

	WidgetWeaponHUD->SetWeaponHUDVisiblity(bVisibility);
}

EWeaponCategory UInventoryComponent::GetCurrentlyEquippedWeaponCategory()
{
	if (HasWeaponEquipped() && CurrentlyEquippedWeapon)
	{
		auto* CurrentlyEquippedWeaponData = CurrentlyEquippedWeapon->GetWeaponData();
		if (!CurrentlyEquippedWeaponData)
			return EWeaponCategory::None;

		return CurrentlyEquippedWeaponData->WeaponCategory;
	}

	return EWeaponCategory::None;
}

bool UInventoryComponent::IsWeaponAlreadyInInventory(AWeapon* NewWeapon) const
{
	if (!IsValid(NewWeapon) || !IsValid(NewWeapon->GetWeaponData()))
	{
		return false;
	}

	UWeaponData* NewWeaponData = NewWeapon->GetWeaponData();

	for (AWeapon* InventoryWeapon : WeaponsInventory)
	{
		if (!IsValid(InventoryWeapon) || !IsValid(InventoryWeapon->GetWeaponData()))
		{
			continue;
		}

		if (InventoryWeapon == NewWeapon)
		{
			continue;
		}

		if (InventoryWeapon->GetWeaponData()->WeaponID == NewWeaponData->WeaponID)
		{
			//AddWeaponToInventoryAsAmmo(NewWeapon);
			return true;
		}
	}

	return false;
}

void UInventoryComponent::SignalPlayerToReload()
{
	ATPCharacter* Player = Cast<ATPCharacter>(GetOwner());
	if (!IsValid(Player) || !Player->GetMesh())
		return;

	Player->SignalToReload();
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

void UInventoryComponent::StartAttackWithCurrentWeapon(const FVector& AimHitLocation)
{
	if (CurrentlyEquippedWeapon)
	{
		CurrentlyEquippedWeapon->StartFire(AimHitLocation);
	}
}

// void UInventoryComponent::StopAttackWithCurrentWeapon()
// {
// 	if (CurrentlyEquippedWeapon)
// 	{
// 		CurrentlyEquippedWeapon->StopFire();
// 	}
// }

void UInventoryComponent::ReloadCurrentlyEquippedWeapon()
{
	if (CurrentlyEquippedWeapon)
	{
		CurrentlyEquippedWeapon->ReloadWeapon();
	}
}

void UInventoryComponent::SetWeaponWidgetHUDRef(UWidgetWeaponHUD* WeaponHUDRef)
{
	WidgetWeaponHUD = WeaponHUDRef;
}

bool UInventoryComponent::GetCanReloadCurrentWeapon()
{
	if (CurrentlyEquippedWeapon)
	{
		auto* Weapon = Cast<AWeaponRanged>(CurrentlyEquippedWeapon);
		return Weapon->GetCanReloadWeapon();
	}
	return false;
}

void UInventoryComponent::UpdateWeaponStats(int32 CurrentAmmo, int32 AmmoClipSize, int32 TotalRemainingSpareAmmo)
{
	if (WidgetWeaponHUD)
	{
		WidgetWeaponHUD->SetCurrentAmmoInClip(CurrentAmmo);
		WidgetWeaponHUD->SetAmmoClipSize(AmmoClipSize);
		WidgetWeaponHUD->SetTotalRemainingSpareAmmo(TotalRemainingSpareAmmo);
	}
	UpdateWeaponImage();
}

void UInventoryComponent::UpdateWeaponImage()
{
	if (WidgetWeaponHUD && CurrentlyEquippedWeapon)
	{
		if (CurrentlyEquippedWeapon->GetWeaponData())
		{
			WidgetWeaponHUD->SetWeaponImage(CurrentlyEquippedWeapon->GetWeaponData()->WeaponImage);
		}
	}
}
