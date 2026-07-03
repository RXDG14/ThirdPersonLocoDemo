#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

enum class EWeaponCategory : uint8;
class UWidgetWeaponHUD;
enum class EWeaponType : uint8;
class AWeapon;

UCLASS()
class THIRDPERSONLOCODEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void PickupWeapon(AWeapon* Weapon);
	void DropCurrentlyEquippedWeapon();
	void HolsterCurrentlyEquippedWeapon();
	void DropAllWeapons();
	void EquipWeaponFromInventory(AWeapon* Weapon);
	const TArray<AWeapon*>& GetWeaponsInventory() const { return WeaponsInventory; }
	bool HasWeaponEquipped() const;
	EWeaponType GetCurrentlyEquippedWeaponType();
	void ChangeWeaponSocket(FName NewWeaponSocketName);
	void AttackWithCurrentWeapon(const FVector& AimHitLocation);
	void ReloadCurrentlyEquippedWeapon();
	void SetWeaponWidgetHUDRef(UWidgetWeaponHUD* WeaponHUDRef);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FName WeaponSocketName;

	UPROPERTY()
	TArray<AWeapon*> WeaponsInventory;

	UPROPERTY()
	AWeapon* CurrentlyEquippedWeapon = nullptr;

	UPROPERTY()
	TObjectPtr<UWidgetWeaponHUD> WidgetWeaponHUD;

	void UpdateWeaponStats(int32 CurrentAmmo, int32 AmmoClipSize, int32 TotalRemainingSpareAmmo);
	void UpdateWeaponImage();
	void AddWeaponToInventory(AWeapon* NewWeapon, bool bShouldHolster);
	void RemoveWeaponFromInventory(AWeapon* Weapon);
	void AddWeaponToInventoryAsAmmo(AWeapon* NewWeapon);
	void EquipWeapon(AWeapon* Weapon);
	void UnEquipWeapon(AWeapon* Weapon, bool bShouldHolster);
	void HolsterWeapon(AWeapon* Weapon);
	void SetPlayerAnimationState(EWeaponType WeaponType);
	void UpdateWeaponUI(bool bVisibility);
	EWeaponCategory GetCurrentlyEquippedWeaponCategory();
};