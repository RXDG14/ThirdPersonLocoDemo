#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;

UCLASS()
class THIRDPERSONLOCODEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void PickupWeapon(AWeapon* Weapon);
	void DropCurrentlyEquippedWeapon();
	void DropAllWeapons();
	void EquipWeaponFromInventory(AWeapon* Weapon);
	const TArray<AWeapon*>& GetWeaponsInventory() const { return WeaponsInventory; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FName WeaponSocketName;

	UPROPERTY()
	TArray<AWeapon*> WeaponsInventory;

	UPROPERTY()
	AWeapon* CurrentlyEquippedWeapon = nullptr;

	void AddWeaponToInventory(AWeapon* NewWeapon, bool bShouldHolster);
	void RemoveWeaponFromInventory(AWeapon* Weapon);
	void AddWeaponToInventoryAsAmmo(AWeapon* NewWeapon);
	void EquipWeapon(AWeapon* Weapon);
	void UnEquipWeapon(AWeapon* Weapon, bool bShouldHolster);
	void HolsterWeapon(AWeapon* Weapon);
	bool HasWeaponEquipped() const;
};