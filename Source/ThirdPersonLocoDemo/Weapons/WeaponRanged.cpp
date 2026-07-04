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
}

void AWeaponRanged::UpdateWeaponStats() // one bullet has been shot so we now update
{
	CurrentAmmoInClip--;
	
	if (CurrentAmmoInClip <= 0)
	{
		TellPlayerToReload.ExecuteIfBound();
		//ReloadWeapon();
	}

	OnWeaponStatsUpdated.ExecuteIfBound(CurrentAmmoInClip, AmmoClipSize, TotalRemainingSpareAmmo);
	
	UE_LOG(LogTemp,Warning,TEXT("CurrentAmmo: %d"),CurrentAmmoInClip);
	UE_LOG(LogTemp,Warning,TEXT("TotalRemainingSpareAmmo: %d"),TotalRemainingSpareAmmo);
}

void AWeaponRanged::StartFire(const FVector& AimHitLocation)
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

void AWeaponRanged::ReloadWeapon()
{
	if (CurrentAmmoInClip == AmmoClipSize)
		return;
	
	if (TotalRemainingSpareAmmo > 0)
	{
		const int32 AmmoNeeded = AmmoClipSize - CurrentAmmoInClip;
		const int32 AmmoToAdd = FMath::Min(AmmoNeeded, TotalRemainingSpareAmmo);

		CurrentAmmoInClip += AmmoToAdd;
		TotalRemainingSpareAmmo -= AmmoToAdd;
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
	if (CurrentAmmoInClip > 0)
	{
		return true;
	}
	else
	{
		return false;	
	}
}

bool AWeaponRanged::GetCanReloadWeapon()
{
	if (TotalRemainingSpareAmmo > 0 && CurrentAmmoInClip < AmmoClipSize)
	{
		return true;
	}
	else
	{
		return false;	
	}
}