#pragma once
#include "CoreMinimal.h"
#include "InventoryComponent.generated.h"


UCLASS()
class THIRDPERSONLOCODEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void PickupWeapon(class AWeapon* Weapon);
	void DropWeapon();
	const TArray<AWeapon*>& GetWeaponsInventory() const { return WeaponsInventory; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory", meta=(AllowPrivateAccess=true))
	FName WeaponSocketName;
	
	UPROPERTY()
	TArray<AWeapon*> WeaponsInventory;

	UPROPERTY()
	class AWeapon* CurrentlyEquippedWeapon;
	
	void AttachWeaponToPlayer(AWeapon* Weapon);
	void DetachWeaponFromPlayer();
	void AddWeaponToInventory(AWeapon* Weapon);
	void RemoveWeaponFromInventory(AWeapon* Weapon);
	void AddWeaponAsAmmo(AWeapon* Weapon);
};