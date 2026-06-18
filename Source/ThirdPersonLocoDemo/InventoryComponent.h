#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSONLOCODEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickupWeapon(AWeapon* Weapon);
	void EquipWeapon();
	void EquipWeaponFromInventory(AWeapon* Weapon);
	void UnEquipWeapon(AWeapon* Weapon);
	void DropWeapon(AWeapon* Weapon);

	int32 GetNumWeapons() const;
	AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	TArray<AWeapon*> WeaponsInInventory;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons", meta=(AllowPrivateAccess="true"))
	AWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess="true"))
	int32 MaxWeapons = 4;
};