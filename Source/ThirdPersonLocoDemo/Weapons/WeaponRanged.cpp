#include "WeaponRanged.h"
#include "Bullet.h"

void AWeaponRanged::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeapon();	
}

void AWeaponRanged::InitializeWeapon()
{
	CurrentAmmoInClip = AmmoClipSize;
	TotalRemainingSpareAmmo = MaxAmmoCapacity;
	SetCanFireWeapon(true);
	SetCanReloadWeapon(true);
}

void AWeaponRanged::Fire(const FVector& AimHitLocation)
{
	if (!GetWorld() || !BulletClass)
		return;

	if (!GetCanFireWeapon())
	{
		// play empty clip sound
		return;
	}
	
	FVector MuzzleLocation = WeaponMuzzle->GetComponentLocation();
	FRotator BulletRotation = (AimHitLocation - MuzzleLocation).Rotation();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	ABullet* SpawnedBullet = GetWorld()->SpawnActor<ABullet>(
		BulletClass,
		MuzzleLocation,
		BulletRotation,
		SpawnParameters);

	if (SpawnedBullet)
	{
		SpawnedBullet->SetBulletDirection(BulletRotation);
		UpdateWeaponStats();
	}
}

void AWeaponRanged::UpdateWeaponStats() // one bullet has been shot so we now update
{
	CurrentAmmoInClip--;
	
	if (CurrentAmmoInClip <= 0)
	{
		ReloadWeapon();
	}

	OnWeaponStatsUpdated.ExecuteIfBound(CurrentAmmoInClip, AmmoClipSize, TotalRemainingSpareAmmo);
	
	UE_LOG(LogTemp,Warning,TEXT("CurrentAmmo: %d"),CurrentAmmoInClip);
	UE_LOG(LogTemp,Warning,TEXT("TotalRemainingSpareAmmo: %d"),TotalRemainingSpareAmmo);
}

void AWeaponRanged::ReloadWeapon()
{
	if (CurrentAmmoInClip == AmmoClipSize)
		return;
	
	if (TotalRemainingSpareAmmo > 0)
	{
		int32 AmmoToAdd = AmmoClipSize - CurrentAmmoInClip;
		CurrentAmmoInClip += AmmoToAdd;
		TotalRemainingSpareAmmo -= AmmoToAdd;
	}
	else
	{
		if (TotalRemainingSpareAmmo < 1 && CurrentAmmoInClip < 1)
		{
			SetCanFireWeapon(false);
			SetCanReloadWeapon(false);
		}
	}

	if (TotalRemainingSpareAmmo > 1 && CurrentAmmoInClip > 1)
	{
		SetCanFireWeapon(true);
		SetCanReloadWeapon(true);
	}
	
	OnWeaponStatsUpdated.ExecuteIfBound(CurrentAmmoInClip, AmmoClipSize, TotalRemainingSpareAmmo);
}

int32 AWeaponRanged::GetCurrentAmmo()
{
	return CurrentAmmoInClip;
}

int32 AWeaponRanged::GetSpareAmmo()
{
	return TotalRemainingSpareAmmo;
}

int32 AWeaponRanged::GetAmmoClipSize()
{
	return AmmoClipSize;
}

bool AWeaponRanged::GetCanFireWeapon()
{
	return bCanFireWeapon;
}

bool AWeaponRanged::GetCanReloadWeapon()
{
	return bCanReloadWeapon;
}

void AWeaponRanged::SetCanFireWeapon(bool value)
{
	bCanFireWeapon = value;
}

void AWeaponRanged::SetCanReloadWeapon(bool value)
{
	bCanReloadWeapon = value;
}