#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponRanged.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API AWeaponRanged : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Fire();
	virtual void Reload();
};
