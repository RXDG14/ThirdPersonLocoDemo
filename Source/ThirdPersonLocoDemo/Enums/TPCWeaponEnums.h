#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None        UMETA(DisplayName = "None"),
	Pistol      UMETA(DisplayName = "Pistol"),
	Rifle       UMETA(DisplayName = "Rifle")
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

UENUM(BlueprintType)
enum class EWeaponCurrentActiveSocket : uint8
{
	Holster        UMETA(DisplayName = "Holster"),
	Equipped       UMETA(DisplayName = "Equipped"),
	Aim            UMETA(DisplayName = "Aim")
};