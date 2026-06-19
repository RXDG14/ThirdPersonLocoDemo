#pragma once

UENUM(Blueprintable)
enum class ETPCWeaponAttackType : uint8
{
	Hitscan       UMETA(DisplayName = "Hitscan"),	
	Projectile    UMETA(DisplayName = "Projectile")	
};

UENUM(Blueprintable)
enum class ETPCWeaponFireMode : uint8
{
	Semi   UMETA(DisplayName = "Semi"),
	Auto   UMETA(DisplayName = "Auto")
};

UENUM(Blueprintable)
enum class ETPCWeaponType : uint8
{
	None    UMETA(DisplayName = "None"),
	Pistol  UMETA(DisplayName = "Pistol"),
	Rifle   UMETA(DisplayName = "Rifle")
};