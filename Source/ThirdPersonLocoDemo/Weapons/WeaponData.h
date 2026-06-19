#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

enum class ETPCWeaponType : uint8;
enum class ETPCWeaponAttackType : uint8;
enum class ETPCWeaponFireMode : uint8;

UCLASS(BlueprintType)
class THIRDPERSONLOCODEMO_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText WeaponName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* WeaponIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AmmoClipSize = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxAmmoCapacity = 240;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETPCWeaponFireMode FireMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETPCWeaponAttackType AttackType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETPCWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;
};