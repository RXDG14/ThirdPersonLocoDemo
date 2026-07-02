#pragma once

#include "CoreMinimal.h"
#include "../Weapons/Weapon.h"
#include "WeaponRanged.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API AWeaponRanged : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Fire(const FVector& AimHitLocation) override;
	virtual void ReloadWeapon() override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes_Weapons", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmoInClip; // 10/30

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes_Weapons", meta = (AllowPrivateAccess = "true"))
	int32 AmmoClipSize = 30; // 30
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes_Weapons", meta = (AllowPrivateAccess = "true"))
	int32 TotalRemainingSpareAmmo; // 20/30__"180<-- total remaining spare ammo"

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes_Weapons", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmoCapacity = 180;

	bool bCanFireWeapon = true;
	bool bCanReloadWeapon = true;

	void InitializeWeapon();
	void UpdateWeaponStats();
	
	bool GetCanFireWeapon();
	void SetCanFireWeapon(bool value);
	bool GetCanReloadWeapon();
	void SetCanReloadWeapon(bool value);
	
};
