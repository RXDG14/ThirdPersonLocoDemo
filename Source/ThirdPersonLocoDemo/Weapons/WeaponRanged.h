#pragma once

#include "CoreMinimal.h"
#include "../Weapons/Weapon.h"
#include "WeaponRanged.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API AWeaponRanged : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire(const FVector& AimHitLocation) override;
	//virtual void StopFire() override;
	virtual void ReloadWeapon() override;
	int32 GetCurrentAmmo();
	int32 GetSpareAmmo();
	int32 GetAmmoClipSize();
	bool GetCanFireWeapon();
	bool GetCanReloadWeapon();
	
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

	FTimerHandle FireTimerHandle;
	FVector CachedAimHitLocation;
	
	//void Fire(const FVector& AimHitLocation);
	void InitializeWeapon();
	void UpdateWeaponStats();
};
