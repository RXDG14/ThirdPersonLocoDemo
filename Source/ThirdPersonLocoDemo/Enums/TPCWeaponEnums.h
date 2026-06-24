#pragma once

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	Melee       UMETA(DisplayName = "Melee"),
	Ranged      UMETA(DisplayName = "Ranged"),
	Throwable   UMETA(DisplayName = "Throwable")
};

UENUM(Blueprintable)
enum class ETPCWeaponState : uint8
{
	Equipped    UMETA(DisplayName = "Equipped"),
	UnEquipped  UMETA(DisplayName = "UnEquipped"),
	Holstered   UMETA(DisplayName = "Holstered")
};

UENUM(BlueprintType)
enum class EWeaponID : uint8
{
	None            = 0  UMETA(DisplayName = "None"),
	Melee_A         = 1  UMETA(DisplayName = "Melee_A"),
	Melee_B         = 2  UMETA(DisplayName = "Melee_B"),
	Pistol_A        = 3  UMETA(DisplayName = "Pistol_A"),
	Pistol_B        = 4  UMETA(DisplayName = "Pistol_B"),
	Rifle_A         = 5  UMETA(DisplayName = "Rifle_A"),
	Rifle_B         = 6  UMETA(DisplayName = "Rifle_B"),
	Throwable_A     = 7  UMETA(DisplayName = "Throwable_A"),
	Throwable_B     = 8  UMETA(DisplayName = "Throwable_B")
};
