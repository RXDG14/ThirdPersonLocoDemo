#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThirdPersonLocoDemo/Enums/TPCWeaponEnums.h"
#include "WeaponData.generated.h"

class AWeapon;

UCLASS(BlueprintType)
class THIRDPERSONLOCODEMO_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	EWeaponID WeaponID = EWeaponID::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	EWeaponType WeaponType = EWeaponType::None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	FText WeaponName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	FName WeaponEquippedSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	FName WeaponHolsterSocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="General")
	TSubclassOf<AWeapon> WeaponClass;
};